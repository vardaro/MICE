
$(document).ready(() => {
    let STATE = JSON.parse(localStorage.getItem("STATE"));
    console.log(STATE);
    $('#curAmount').html(() =>{
        return STATE.cash_register;
    });
    $('#order-dashboard').html(() => {
        let length = STATE.orders.length;

        let outputHTML = `<h3 style="margin-bottom: 2rem;">Unfilled Orders</h3>`;
        for (let i = 0; i < length; i++) {
            let curOrder = STATE.orders[i];

            // filter only by unfilled orders
            if (curOrder.status == 'unfilled') {

                outputHTML += 
                `
                <div class="row" style="margin-bottom: 4rem;">

                    <div class="card" style="width: 90%">
                    
                        <div class="card-body">
                            <h4 class="card-title"><a>Order ${curOrder.orderNumber + 1} (${curOrder.status})</a></h4>
                            ${(()=>{
                                let out = ``
                                curOrder.servings.map((cur, index) => {
                                    out += 
                                    `
                                        <p class="card-text">
                                            <strong>Serving: </strong> ${index + 1}
                                            <br>
                                            <strong>Price: </strong> ${cur.price} 
                                            <br>
                                            <strong>Container: </strong> ${cur.container.name}
                                            <br>
                                            <strong>Scoops: </strong> ${cur.scoops.map(cur => {return cur.name}).join(', ')}
                                            <br>
                                            <strong>Toppings: </strong> ${cur.toppings.map(cur => {return cur.name}).join(', ')}
                                            
                                        </p>
                                        
                                    `;
                                });
                                return  out;
                            })()}
                            <a id="fillOrder" name="${i}" class="btn btn-primary">Fill</a>
                            <a href="#" class="btn btn-danger">Cancel</a>
                            
                            </div>
                        </div>
                </div>
                `;
            

            }
        }
        outputHTML += `<h3 style="margin-bottom: 2rem;">Filled/Cancelled Orders</h3>`;
        for (let i = 0; i < length; i++) {
            let curOrder = STATE.orders[i];
            if (curOrder.status == "unfilled") continue;
            outputHTML += `<div class="row" style="margin-bottom: 4rem;">
            
                                <div class="card" style="width: 90%">
                                
                                    <div class="card-body">
                                        <h4 class="card-title"><a>Order ${curOrder.orderNumber + 1} (${curOrder.status})</a></h4>
                                        ${(()=>{
                                            let out = ``
                                            curOrder.servings.map((cur, index) => {
                                                out += 
                                                `
                                                    <p class="card-text">
                                                        <strong>Serving: </strong> ${index + 1}
                                                        <br>
                                                        <strong>Price: </strong> ${cur.price} 
                                                        <br>
                                                        <strong>Container: </strong> ${cur.container.name}
                                                        <br>
                                                        <strong>Scoops: </strong> ${cur.scoops.map(cur => {return cur.name}).join(', ')}
                                                        <br>
                                                        <strong>Toppings: </strong> ${cur.toppings.map(cur => {return cur.name}).join(', ')}
                                                        
                                                    </p>
                                                    
                                                `;
                                            });
                                            return  out;
                                        })()}
                                        </div>
                                </div>
                            </div>`;
        }
        return outputHTML;
    });


    $('#inventory-dashboard').html(() => {
        // build a table to container, topping, and scoop
        let outputHTML = ``;

        //container
        outputHTML += `<h3 style="margin-bottom: 2rem;">Containers</h3>` + getObjectTableHTML(STATE.containers);
        //scoops
        outputHTML += `<h3 style="margin-bottom: 2rem;">Scoops</h3>` + getObjectTableHTML(STATE.scoops);
        //toppings
        outputHTML += `<h3 style="margin-bottom: 2rem;">Toppings</h3>` + getObjectTableHTML(STATE.toppings);
        
        return outputHTML;
    });

    function getObjectTableHTML(arrayOfObject) {
        let outputHTML = ``;

            outputHTML += 
            `
            <table class="table" style="margin-bottom: 4rem;">
            
                <!--Table head-->
                <thead>
                    <tr>
                        <th>#</th>
                        <th>Name</th>
                        <th>Stock</th>
                        <th>RP</th>
                        <th>WP</th>
                        
                    </tr>
                </thead>
              <!--Table head-->
            
                <!--Table body-->
                <tbody>
                    ${(() => {
                        let out = ``;
                        arrayOfObject.map((cur, index) => {
                            out += 
                            `
                            <tr>
                            <th scope="row">${index}</th>
                            <td>${cur.name}</td>
                            <td>${cur.stockRemaining}</td>
                            <td>$${cur.retailCost}</td>
                            <td>$${cur.wholesaleCost}</td>
                            </tr>
                            `;
                        }); 
                        return out;                     
                    })()}
                </tbody>
                <!--Table body-->
            
            </table>
            `

        return outputHTML;
    }

    function getServingHTML(serving) {
        let outputHTML = `
        <div>Price: $${serving.price}</div>
        <div>${serving.container.name}</div><div>`;
        serving.scoops.map(cur => {
            outputHTML += `${cur.name}, `; 
        });
        outputHTML += `</div><div>`;
        serving.toppings.map(cur => {
            outputHTML += `${cur.name}, `;
        });

        return outputHTML += `</div>`;
    }

    // When the click create customer on the nav, show this form...
    $('#customer-maker').click(e => {
        console.log('hey');
        // html of the form...
        let form = `
        <form>
            <div class="row">
                <div class="six columns">
                    <label for="name">Customer Name</label>
                    <input class="u-full-width" type="text" id="name">
                </div>
            </div>
        
            <div class="row">
                <div class="three columns">
                    <label for="number">Phone number</label>
                    <input class="u-full-width" type="number" id="number">
                </div>
                <div class="three columns">
                    <label for="cid">Customer ID</label>
                    <input class="u-full-width" type="number" id="cid">
                </div>
            </div>
        
            <input class="button-primary customer-submit" type="submit" value="Submit">
        </form>`;
        // set it to the main window
        $('#body').html(form);
    });

    // when they click submit on the server form...
    $(document).on('click', '.customer-submit', e => {
        e.preventDefault();
        // make an ajax request to make the new server
        let name = $('#name').val();
        let employeeID = $('#cid').val();
        let wage = $('#number').val();        
        let customer = {
            name: name,
            customerID: employeeID,
            phoneNumber: wage
        };
        console.log(customer);
        $.ajax({
            type: "POST",
            url: '/api/create_customer',
            data: customer,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                location.reload();
            },
        });
    });

    $(document).on('click', '#fillOrder', e=> {
        console.log(e);
        let indexToFill = parseInt(e.target.name);
        console.log(indexToFill);
        $.ajax({
            type: "POST",
            url: `/api/fill_order/${indexToFill}`,
            success: (data) => {
                console.log(data);
                STATE = data;

                // store new state in local storage for cross page access
                localStorage.setItem("STATE", JSON.stringify(data));
                location.reload();
            },
        });
    });

});