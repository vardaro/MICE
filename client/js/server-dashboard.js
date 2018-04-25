
$(document).ready(() => {
    let STATE = JSON.parse(localStorage.getItem("STATE"));
    console.log(STATE);
    
    $('#order-dashboard').html(() => {
        let length = STATE.orders.length;

        let outputHTML = ``;
        for (let i = 0; i < length; i++) {
            let curOrder = STATE.orders[i];

            // filter only by unfilled orders
            if (curOrder.status == 'unfilled') {

                outputHTML += 
                `
                <div class="row" style="margin-bottom: 4rem;">

                    <div class="col-lg-6">
                    <div class="card">
                    
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
                            <a href="#" class="btn btn-primary">Fill</a>
                            <a href="#" class="btn btn-danger">Cancel</a>
                            
                            </div>
                        </div>
                    </div>
                </div>
                `;
            

            }
        }
        return outputHTML;
    });

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

});