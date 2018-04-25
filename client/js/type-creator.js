$(document).ready(() => {

    let STATE = localStorage.getItem("STATE");


    $('.container-submit').click(createContainer);
    $('.scoop-submit').click(createScoop);
    $('.topping-submit').click(createTopping);

    // makes a POST to api to create a container
    function createContainer(e) {
        e.preventDefault();

        let name = $('#name').val();
        let desc = $('#desc').val();
        let wc = $('#wc').val();
        let rc = $('#rc').val();
        let stock = $('#stk').val();
        let img = $('#img').val();
        let scoops = $('#scoop').val();

        let container = {
            name: name,
            description: desc,
            wholesaleCost: wc,
            retailCost: rc,
            stockRemaining: stock,
            img: img,
            scoopCount: scoops
        };

        $.ajax({
            type: "POST",
            url: '/api/create_container',
            data: container,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                parent.history.back();
            },
        });
    }

    function createScoop(e) {
        e.preventDefault();

        let name = $('#name').val();
        let desc = $('#desc').val();
        let wc = $('#wc').val();
        let rc = $('#rc').val();
        let stock = $('#stk').val();
        let img = $('#img').val();

        let scoop = {
            name: name,
            description: desc,
            wholesaleCost: wc,
            retailCost: rc,
            stockRemaining: stock,
            img: img
        };

        $.ajax({
            type: "POST",
            url: '/api/create_scoop',
            data: scoop,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                parent.history.back();
            },
        });

    }

    function createTopping(e) {
        e.preventDefault();

        let name = $('#name').val();
        let desc = $('#desc').val();
        let wc = $('#wc').val();
        let rc = $('#rc').val();
        let stock = $('#stk').val();
        let img = $('#img').val();

        let topping = {
            name: name,
            description: desc,
            wholesaleCost: wc,
            retailCost: rc,
            stockRemaining: stock,
            img: img
        };

        $.ajax({
            type: "POST",
            url: '/api/create_topping',
            data: topping,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                parent.history.back();
            },
        });

    }
});