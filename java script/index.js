const toggleBtn = document.getElementById('toggleBtn');
const info = document.getElementById('info');

toggleBtn.addEventListener('click', () => {
    info.classList.toggle('hidden'); // يضيف/يحذف الكلاس hidden

    if (info.classList.contains('hidden')) {
        toggleBtn.innerText = "show ";
    } else {
        toggleBtn.innerText = "hidden ";
    }
});






