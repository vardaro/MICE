$(document).ready(() => {
    let STATE = JSON.parse(localStorage.getItem("STATE"));
    console.log(STATE);
    let ORDER = {
        servings: [],
    }

    // populate the container field
    function getContainerForm(servingIndex) {
        let targetHTML = ``;

        for (let i = 0; i < STATE.containers.length; i++) {
            let cur = STATE.containers[i];
            if (cur.stockRemaining < 1) continue; // filter out products out of stock!
            let curInnerHTML = `

            <div class="row" style="margin-bottom: 2rem;">
            <div class="col-md-12">
                <div class="card">
                    <div class="card-body">
                        <h4 class="card-title">${cur.name} - <span style="color: green">$${cur.retailCost}</span></h4>
                        <p class="card-text">
                            <strong>Scoops: </strong> ${cur.scoopCount}
                            <br>
                            ${cur.description}
                        
                        </p>
                        <button class="container-button btn btn-primary" id="${servingIndex}" name="${i}">Select</button>               
                    </div>
                </div>
            </div>
            </div>
            
            `;

            targetHTML += curInnerHTML;
        }
        return '<h1 class="h1" style="margin-top: 2rem;">Container</h1>' + targetHTML;

    }

    // populate toppings
    function getToppingForm(servingIndex) {
        let targetHTML = ``;

        for (let i = 0; i < STATE.toppings.length; i++) {
            let cur = STATE.toppings[i];
            if (cur.stockRemaining < 1) continue; // filter out products out of stock!
            
            let curInnerHTML = `
            <div class="row" style="margin-bottom: 2rem;">
                <div class="col-md-12">
                    <div class="card">
                        <div class="card-body">
                            <h4 class="card-title">${cur.name} - <span style="color: green">$${cur.retailCost}</span></h4>
                            <p class="card-text">
                                ${cur.description}
                            </p>
                            <label for="${servingIndex}">Number of toppings</label>
                            <input class="topping-input form-control" style="width: 70px" name="${i}" id="${servingIndex}" type="number">            
                        </div>
                    </div>
                </div>
            </div>`;

            targetHTML += curInnerHTML;
        }
        return '<h1 class="h1" style="margin-top: 2rem;">Toppings</h1>' + targetHTML;

    }

    // populate the scoop field
    function getScoopForm(servingIndex) {
        let targetHTML = ``;

        for (let i = 0; i < STATE.scoops.length; i++) {
            let cur = STATE.scoops[i];
            if (cur.stockRemaining < 1) continue; // filter out products out of stock!
            
            let curInnerHTML = `
            <div class="row" style="margin-bottom: 2rem;">
                <div class="col-md-12">
                    <div class="card">
                        <div class="card-body">
                            <h4 class="card-title">${cur.name} - <span style="color: green">$${cur.retailCost}</span></h4>
                            <p class="card-text">
                                ${cur.description}
                            </p>
                            <label for="${servingIndex}">Number of scoops</label>
                            <input class="scoop-input form-control" style="width: 70px" name="${i}" id="${servingIndex}" type="number">  
                        </div>
                    </div>
                </div>

            </div>
            `;

            targetHTML += curInnerHTML;
        }
        return '<h1 class="h1" style="margin-top: 2rem;">Scoops</h1>' + targetHTML;

    }

    // a function that accepts a class selector,
    // and then returns an object for each element of that class type with a value
    function getInputsOf(classSelector) {
        // get all the inputs with a and return an object representing relevant data
        let inputs = $(classSelector).map(function () {
            if (this.value) {
                return {
                    amount: parseInt(this.value),
                    index: parseFloat(this.name),
                }
            }
        }).get();
        
        return inputs;
    }

    function getServingForm(id) {
        let target = `
        <div id="${id}">
        <div class="">${getContainerForm(id)}</div>
        <div class="">${getScoopForm(id)}</div>
        <div class="">${getToppingForm(id)}</div>
        </div>
        `;
        return target;
    }

    function buildAccordion(numServings) {
        let target = "";

        for (let i = 0; i < numServings; i++) {
            // pass the index as the id so it can easily be recognized which serving it corresponds to
            target += `
            <h3 class="h3" style="margin-top: 5rem;">Serving ${i + 1}</h3>
            <div>${getServingForm(i)}</div>
            `;
            ORDER.servings[i] = {};
        }
        $('#accordion').html(target + '<input type="button" class="btn btn-success order" value="Place Order">');
        // $('#accordion').accordion();
    }

    $('#serving-count').change(e => {
        let numServings = $('#serving-count').val();
        buildAccordion(numServings);
        $('#servings').html(numServings);

        // hide the number input now
        $('#serving-count').hide();
        $('#serving-input-label').hide();

    });

    // A function that will calc the total for an order
    function calculateTotal() {
        let sum = 0.0;
        console.log(ORDER);
        // iterate over the ORDER object
        for (let prop in ORDER) {
            if (ORDER.hasOwnProperty(prop) && Array.isArray(ORDER[prop])) {

                // now iterate over  current object (which should be an array)
                // and add the current objects ammount * price to the sum
                let cur = ORDER[prop];
                cur.map((iteration) => {
                    sum += (iteration.amount || 1) * iteration.retailCost;
                });
            }
        }
        $('#orderTotal').html(sum);
    }

    $(document).on('click', '.container-button', (e) => {
        // get index of container and index of serving being modified
        let containerIndex = parseInt(e.target.name);
        let servingIndex = parseInt(e.target.id);
        let container = STATE.containers[containerIndex];

        // apply to the servings array
        ORDER.servings[servingIndex].container = container;
        ORDER.servings[servingIndex].containerIndex = containerIndex;
        $('#' + servingIndex + '.container-button').hide();
    });

    $(document).on('change', '.scoop-input', e => {
        // perform data validation on the input
        // get the max number of scoops
        let servingIndex = parseInt(e.target.id);
        // let scoopIndex = parseInt(e.target.name);

        // get the array of inpts 
        let inputs = getInputsOf('#' + servingIndex + '.scoop-input');

        let scoopArray = [];
        let scoopIndex = [];
        inputs.map(cur => {
            for (let i = 0; i < cur.amount; i++) {
                scoopArray.push(STATE.scoops[cur.index]);
                scoopIndex.push(cur.index);
            }
        });

        ORDER.servings[servingIndex].scoops = scoopArray;
        ORDER.servings[servingIndex].scoopIndexes = scoopIndex;
    });

    $(document).on('change', '.topping-input', e => {
        // perform data validation on the input
        // get the max number of topping
        let servingIndex = parseInt(e.target.id);
        let scoopIndex = parseInt(e.target.name);

        // get the array of inpts 
        let inputs = getInputsOf('#' + servingIndex + '.topping-input');
        let toppingArray = [];
        let toppingIndex = [];
        inputs.map(cur => {
            for (let i = 0; i < cur.amount; i++) {
                toppingArray.push(STATE.toppings[cur.index]);
                toppingIndex.push(cur.index);
            }
        });
        ORDER.servings[servingIndex].toppings = toppingArray;
        ORDER.servings[servingIndex].toppingIndexes = toppingIndex;
    });

    // Make a POST to the API
    $(document).on('click', '.order', e => {
        e.preventDefault();
        ORDER.status = "unfilled";
        console.log(ORDER);
        $.ajax({
            type: "POST",
            url: '/api/create_order',
            data: ORDER,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                parent.history.back();
            },
        });

    });

});