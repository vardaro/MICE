$(document).ready(() => {

    let STATE = JSON.parse(localStorage.getItem("STATE"));


    $('#container-maker').click(e => {
        $('#body').html(e => {
            return `
            <div class="row">
                <div class="col-md-6">
                    <form>
                        <p class="h4 text-center mb-4">Create New Container</p>
    
                        <label for="name" class="grey-text">Container name</label>
                        <input type="text" id="name" class="form-control">
    
                        <br>
    
                        <label for="wc" class="grey-text">Wholesale cost</label>
                        <input type="text" id="wc" class="form-control">
    
                        <br>
    
                        <label for="rc" class="grey-text">Retail cost</label>
                        <input type="text" id="rc" class="form-control">
    
                        <br>

                        <label for="sr" class="grey-text">Stock remaining</label>
                        <input type="text" id="sr" class="form-control">

                        <br>
                        
                        <label for="img" class="grey-text">Image path</label>
                        <input type="text" id="img" class="form-control">
                        
                        <br>
                        
                        <label for="scoopcount" class="grey-text">Scoop count</label>
                        <input type="text" id="scoopcount" class="form-control">

                        <br>

                        <label for="desc">Description</label>
                        <textarea class="form-control" id="desc"></textarea>

                        <div class="text-center mt-4">
                            <button class="btn btn-outline-purple container-submit" type="submit">Submit
                                <i class="fa fa-paper-plane-o ml-2"></i>
                            </button>
                        </div>
                    </form>
                </div>
    
                <div class="col-md-6">
                    ${(() => {
                    if (!STATE.containers || !STATE.containers.length) return '';

                    let out = ``;
                    for (let i = 0; i < STATE.containers.length; i++) {
                        let cur = STATE.containers[i];
                        out += `
                            <div class="card" style="margin-bottom: 4rem;">
                                <div class="card-body">
                                    <h4 class="card-title"><a>${cur.name}</a></h4>
                                    <p class="card-text">
                                    <strong>Retail cost: </strong> ${cur.restailCost}
                                    <br>
                                    <strong>Wholesale cost: </strong> ${cur.wholesaleCost}
                                    <br>
                                    <strong>Stock Filled: </strong> ${cur.stockRemaining}
                                    <br>
                                    <strong>Description: </strong> ${cur.description}
                                    </p>
                                    <button type="button" name="containers" id="${i}" class="btn btn-primary open-modal">
                                    Restock
                                    </button>
                                </div>
                            </div>`;
                    }
                    return out;
                })()}
                </div>
    
            </div>`
        });
    });

    $(document).on('click', '.container-submit', createContainer);

    $('#scoop-maker').click(e => {
        $('#body').html(e => {
            return `
            <div class="row">
                <div class="col-md-6">
                    <form>
                        <p class="h4 text-center mb-4">Create New Container</p>
    
                        <label for="name" class="grey-text">Container name</label>
                        <input type="text" id="name" class="form-control">
    
                        <br>
    
                        <label for="wc" class="grey-text">Wholesale cost</label>
                        <input type="text" id="wc" class="form-control">
    
                        <br>
    
                        <label for="rc" class="grey-text">Retail cost</label>
                        <input type="text" id="rc" class="form-control">
    
                        <br>

                        <label for="sr" class="grey-text">Stock remaining</label>
                        <input type="text" id="sr" class="form-control">

                        <br>
                        
                        <label for="img" class="grey-text">Image path</label>
                        <input type="text" id="img" class="form-control">
                        
                        <br>

                        <label for="desc">Description</label>
                        <textarea class="form-control" id="desc"></textarea>

                        <div class="text-center mt-4">
                            <button class="btn btn-outline-purple scoop-submit" type="submit">Submit
                                <i class="fa fa-paper-plane-o ml-2"></i>
                            </button>
                        </div>
                    </form>
                </div>
    
                <div class="col-md-6">
                    ${(() => {
                    if (!STATE.scoops || !STATE.scoops.length) return '';

                    let out = ``;
                    for (let i = 0; i < STATE.scoops.length; i++) {
                        let cur = STATE.scoops[i];
                        out += `
                            <div class="card" style="margin-bottom: 4rem;">
                                <div class="card-body">
                                    <h4 class="card-title"><a>${cur.name}</a></h4>
                                    <p class="card-text">
                                    <strong>Retail cost: </strong> ${cur.restailCost}
                                    <br>
                                    <strong>Wholesale cost: </strong> ${cur.wholesaleCost}
                                    <br>
                                    <strong>Stock Filled: </strong> ${cur.stockRemaining}
                                    <br>
                                    <strong>Description: </strong> ${cur.description}
                                    </p>
                                    <button type="button" name="scoops" id="${i}" class="btn btn-primary open-modal">
                                    Restock
                                    </button>
                                </div>
                            </div>`;
                    }
                    return out;
                })()}
                </div>
    
            </div>`
        });
    });

    $(document).on('click', '.scoop-submit', createScoop);

    $('#topping-maker').click(e => {
        $('#body').html(e => {
            return `
            <div class="row">
                <div class="col-md-6">
                    <form>
                        <p class="h4 text-center mb-4">Create New Container</p>
    
                        <label for="name" class="grey-text">Container name</label>
                        <input type="text" id="name" class="form-control">
    
                        <br>
    
                        <label for="wc" class="grey-text">Wholesale cost</label>
                        <input type="text" id="wc" class="form-control">
    
                        <br>
    
                        <label for="rc" class="grey-text">Retail cost</label>
                        <input type="text" id="rc" class="form-control">
    
                        <br>

                        <label for="sr" class="grey-text">Stock remaining</label>
                        <input type="text" id="sr" class="form-control">

                        <br>
                        
                        <label for="img" class="grey-text">Image path</label>
                        <input type="text" id="img" class="form-control">
                        
                        <br>

                        <label for="desc">Description</label>
                        <textarea class="form-control" id="desc"></textarea>

                        <div class="text-center mt-4">
                            <button class="btn btn-outline-purple topping-submit" type="submit">Submit
                                <i class="fa fa-paper-plane-o ml-2"></i>
                            </button>
                        </div>
                    </form>
                </div>
    
                <div class="col-md-6">
                    ${(() => {
                    if (!STATE.toppings || !STATE.toppings.length) return '';

                    let out = ``;
                    for (let i = 0; i < STATE.toppings.length; i++) {
                        let cur = STATE.toppings[i];
                        out += `
                            <div class="card" style="margin-bottom: 4rem;">
                                <div class="card-body">
                                    <h4 class="card-title"><a>${cur.name}</a></h4>
                                    <p class="card-text">
                                    <strong>Retail cost: </strong> ${cur.restailCost}
                                    <br>
                                    <strong>Wholesale cost: </strong> ${cur.wholesaleCost}
                                    <br>
                                    <strong>Stock Filled: </strong> ${cur.stockRemaining}
                                    <br>
                                    <strong>Description: </strong> ${cur.description}
                                    </p>
                                    <button type="button" name="toppings" id="${i}" class="btn btn-primary open-modal">
                                    Restock
                                    </button>
                                </div>
                            </div>`;
                    }
                    return out;
                })()}
                </div>
    
            </div>`
        });
    });

    $(document).on('click', '.topping-submit', createTopping);

    // object that hold data to be restocked, eventually gets sents to api
    let restockObject = {};

    $(document).on('click', '.open-modal', e => {
        let id = parseInt(e.target.id); // the id of target contains the index of the item we wanna mutate
        let typeOfItem = e.target.name;

        // reassign the restock object
        restockObject = {
            index: id,
            type: typeOfItem
        };

        // now open that model
        $('#restockModal').modal('show')

    });

    // function that sends a restock request to the api!
    $(document).on('click', '#restockSubmit', e => {
        let amountToRestock = $('#restockAmount').val();
        console.log(amountToRestock);
        if (!amountToRestock) {
            alert('WTF');
            return;
        }
        
        $.ajax({
            type: "POST",
            url: "/api/restock_item",
            data: {
                index: restockObject.index,
                type: restockObject.type,
                amount: amountToRestock
            },
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                location.reload();
            }
        });
    });

    // makes a POST to api to create a container
    function createContainer(e) {
        e.preventDefault();

        let name = $('#name').val();
        let desc = $('#desc').val();
        let wc = $('#wc').val();
        let rc = $('#rc').val();
        let stock = $('#sr').val();
        let img = $('#img').val();
        let scoops = $('#scoopcount').val();

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
                location.reload();
            },
        });
    }

    function createScoop(e) {
        e.preventDefault();

        let name = $('#name').val();
        let desc = $('#desc').val();
        let wc = $('#wc').val();
        let rc = $('#rc').val();
        let stock = $('#sr').val();
        let img = $('#img').val();

        let scoop = {
            name: name,
            description: desc,
            wholesaleCost: wc,
            retailCost: rc,
            stockRemaining: stock,
            img: img
        };

        console.log(scoop);
        $.ajax({
            type: "POST",
            url: '/api/create_scoop',
            data: scoop,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                location.reload();
            },
        });

    }

    function createTopping(e) {
        e.preventDefault();

        let name = $('#name').val();
        let desc = $('#desc').val();
        let wc = $('#wc').val();
        let rc = $('#rc').val();
        let stock = $('#sr').val();
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
                location.reload();
            },
        });

    }
});