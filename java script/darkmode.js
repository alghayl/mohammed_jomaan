const btn = document.getElementById('themeBtn');
const body = document.body;

// عند تحميل الصفحة: تحقق من الوضع المحفوظ
if (localStorage.getItem('theme') === 'dark') {
    body.classList.add('dark-mode');
    btn.innerText = "light ";
} else {
    btn.innerText = "dark ";
}

// عند الضغط على الزر: غيّر وخزّن
btn.addEventListener('click', () => {
    body.classList.toggle('dark-mode');

    if (body.classList.contains('dark-mode')) {
        localStorage.setItem('theme', 'dark');
        btn.innerText = "light";
    } else {
        localStorage.setItem('theme', 'light');
        btn.innerText = "dark";
    }
});


const toggle = document.getElementById("menu-toggle");
const navLinks = document.getElementById("nav-list");

toggle.addEventListener("click", () => {
    navLinks.classList.toggle("show");});