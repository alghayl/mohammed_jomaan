document.addEventListener('DOMContentLoaded', () => {
    // عناصر رسائل الخطأ/النجاح (لو موجودة في الصفحة)
    const showMessage = (type, text) => {
        const errorEl = document.querySelector('.error-message');
        const successEl = document.querySelector('.success-massage');
        if (type === 'error') {
            if (errorEl) errorEl.textContent = text, errorEl.style.display = 'block';
            if (successEl) successEl.style.display = 'none';
        } else {
            if (successEl) successEl.textContent = text, successEl.style.display = 'block';
            if (errorEl) errorEl.style.display = 'none';
        }
    };

    // إدارة المستخدمين في localStorage
    const getUsers = () => {
        const raw = localStorage.getItem('users');
        if (!raw) return [];
        try {
            const parsed = JSON.parse(raw);
            return Array.isArray(parsed) ? parsed : [];
        } catch {
            localStorage.removeItem('users');
            return [];
        }
    };

    const saveUsers = (users) => localStorage.setItem('users', JSON.stringify(users));

    // ----------- تسجيل الحساب -----------
    const registerForm = document.getElementById('regesterform');
    if (registerForm) {
        registerForm.addEventListener('submit', (e) => {
            e.preventDefault();

            const first = document.getElementById('first').value.trim();
            const last = document.getElementById('last').value.trim();
            const age = document.getElementById('age').value.trim();
            const phone = document.getElementById('phone').value.trim();
            const dob = document.getElementById('date').value;
            const nationality = document.getElementById('nationality').value;
            const gender = document.querySelector('input[name="gender"]:checked');
            const email = document.getElementById('email').value.trim().toLowerCase();
            const password = document.getElementById('password').value;
            const confirmPassword = document.getElementById('chpassword').value;

            if (!first || !last || !age || !phone || !dob || !nationality || !gender || !email || !password || !confirmPassword) {
                return showMessage('error', 'Please fill in all fields.');
            }

            if (parseInt(age) < 18) return showMessage('error', 'Age must be 18 or older.');
            if (!/^\+?\d{9,15}$/.test(phone)) return showMessage('error', 'Invalid phone number.');
            if (!/^\S+@\S+\.\S+$/.test(email)) return showMessage('error', 'Invalid email.');
            if (password.length < 6) return showMessage('error', 'Password must be at least 6 characters.');
            if (password !== confirmPassword) return showMessage('error', 'Passwords do not match.');

            const users = getUsers();
            if (users.some((u) => u.email === email)) return showMessage('error', 'Email is already registered.');

            users.push({ first, last, age, phone, dob, nationality, gender: gender.id, email, password });
            saveUsers(users);

            showMessage('success', 'Account created successfully!');
            registerForm.reset();

            setTimeout(() => window.location.href = 'log in .html', 2000);
        });
    }

    // ----------- تسجيل الدخول -----------
    const loginForm = document.getElementById('loginForm');
    if (loginForm) {
        loginForm.addEventListener('submit', (e) => {
            e.preventDefault();

            const userInput = document.getElementById('username').value.trim().toLowerCase();
            const passwordInput = document.getElementById('password').value;

            if (!userInput || !passwordInput) return showMessage('error', 'Please fill in all fields.');

            const users = getUsers();
            const found = users.find(u => u.email.toLowerCase() === userInput);

            if (!found) return showMessage('error', 'User not found.');
            if (found.password !== passwordInput) return showMessage('error', 'Incorrect password.');

            sessionStorage.setItem('currentUser', found.email);
            showMessage('success', `Welcome ${ found.first }! Redirecting...`);

            setTimeout(() => window.location.href = '../index.html', 1500);
        });
    }
});