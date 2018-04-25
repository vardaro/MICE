$(document).ready(() => {
    let STATE = JSON.parse(localStorage.getItem("STATE"));
    console.log(STATE);

    // When the click create server on the nav, show this form...
    $('#server-maker').click(e => {
        // html of the form...
        let form = `
        <div class="row">
            <div class="col-md-6">
                <form>
                    <p class="h4 text-center mb-4">Create New Server</p>

                    <label for="defaultFormSubscriptionNameEx" class="grey-text">Server name</label>
                    <input type="text" id="name" class="form-control">

                    <br>

                    <label for="defaultFormSubscriptionEmailEx" class="grey-text">Starting wage</label>
                    <input type="email" id="wage" class="form-control">

                    <br>

                    <label for="defaultFormSubscriptionEmailEx" class="grey-text">Server ID</label>
                    <input type="email" id="eid" class="form-control">

                    <div class="text-center mt-4">
                        <button class="btn btn-outline-purple server-submit" type="submit">Submit
                            <i class="fa fa-paper-plane-o ml-2"></i>
                        </button>
                    </div>
                </form>
            </div>

            <div class="col-md-6">
                ${(() => {
                    if (!STATE.servers.length) return '';

                    let out = ``;
                    for (let i = 0; i < STATE.servers.length; i++) {
                        let cur = STATE.servers[i];
                        out += `
                        <div class="card" style="margin-bottom: 4rem;">
                            <div class="card-body">
                                <h4 class="card-title"><a>${cur.name}</a></h4>
                                <p class="card-text">
                                <strong>Employee ID: </strong> ${cur.employeeID}
                                <br>
                                <strong>Wage: </strong> ${cur.wage}
                                <br>
                                <strong>Orders Filled: </strong> ${cur.numOrders}
                                </p>
                                <a href="#" class="btn btn-danger">fire them</a>
                            </div>
                        </div>`;
                    }
                    return out;
                })()}
            </div>

        </div>`;
        // set it to the main window
        $('#body').html(form);
    });

    // when they click submit on the server form...
    $(document).on('click', '.server-submit', e => {
        e.preventDefault();
        // make an ajax request to make the new server
        let name = $('#name').val();
        let employeeID = $('#eid').val();
        let wage = $('#wage').val();
        let server = {
            name: name,
            employeeID: employeeID,
            wage: wage
        };
        console.log(server);
        $.ajax({
            type: "POST",
            url: '/api/create_server',
            data: server,
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