document.addEventListener('DOMContentLoaded', function() {

    var modalButtons = document.querySelectorAll('.js-open-modal'),
        overlay = document.querySelector('.js-overlay-modal'),
        closeButtons = document.querySelectorAll('.js-modal-close'),
        request = new XMLHttpRequest();

    modalButtons.forEach(function(item) {
        item.addEventListener('click', function(e) {
            history.pushState({ page: 1 }, "tttt1", "?modal");
            try {
                inputs[0].value = localStorage.key(localStorage.length - 1);
                inputs[1].value = localStorage.getItem(localStorage.key(localStorage.length - 1));
            } finally {
                statusMessage.innerHTML = '';

                e.preventDefault();

                var modalId = this.getAttribute('data-modal'),
                    modalElem = document.querySelector('.modal[data-modal="' + modalId + '"]');

                modalElem.classList.add('active');
                overlay.classList.add('active');
            }
        });

    });


    closeButtons.forEach(function(item) {

        item.addEventListener('click', function(e) {
            var parentModal = this.closest('.modal');

            parentModal.classList.remove('active');
            overlay.classList.remove('active');
            window.history.back();
        });

    });

    document.body.addEventListener('keyup', function(e) {
        var key = e.keyCode;

        if (key == 27) {

            document.querySelector('.modal.active').classList.remove('active');
            document.querySelector('.overlay').classList.remove('active');
        };
    }, false);


    overlay.addEventListener('click', function() {
        document.querySelector('.modal.active').classList.remove('active');
        this.classList.remove('active');
    });
    let message = {
        loading: 'loading, please wait...',
        success: 'data has been sent!',
        failure: 'something went wrong...'
    };
    let form = document.querySelector('.main'),
        statusMessage = document.createElement('div'),
        input = document.querySelector('input[type=submit]'),
        inputs = document.querySelectorAll('input[type=text], input[type=email]');
    form.appendChild(statusMessage);

    input.addEventListener('click', function(event) {
        let key = inputs[0].value;
        let value = inputs[1].value;

        localStorage.setItem(key, value);

    });

    formcarry({
        form: "TzAj7npIjX",
        element: "#my-formcarry",
        extraData: {
            screenSize: `${window.screen.width}x${window.screen.height}`,
            language: window.navigator.language,
        },
        onSuccess: function(response) {
            statusMessage.innerHTML = message.success;
            for (var i = 0; i < inputs.length; i++) {
                inputs[i].value = '';
            };
        },
        onError: function(error) {
            statusMessage.innerHTML = message.failure;
        }
    });


});
