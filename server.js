'use strict'
const MICE = require('./MICE/build/Release/mice');

const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const PORT = process.env.PORT || 3000;
const mongoose = require('mongoose');
const Schema = mongoose.Schema;
const STATE_ID = '5adfc4dde2714b3c60620bc0'; //lol

// connect to the db
mongoose.connect(process.env.DB || require('./secret'));

let emporiumSchema = new Schema({}, { strict: false }); // im laazzy so im setting strict to fallse here
let Emporium = mongoose.model('Emporium', emporiumSchema);

// load the data from the db first
Emporium.findById('5adfc4dde2714b3c60620bc0', (err, data) => {
    MICE.loadState(data._doc);
    console.log(MICE.getState());
});

// returns the state, but also adjusts the db
const getState = (cb) => {
    let state = MICE.getState();

    Emporium.findByIdAndUpdate(STATE_ID, state, (err, data) => {
        if (err) console.log(err);
        cb(state);
    });

};

// set up the express server
app.use(bodyParser.urlencoded({ limit: '50mb', extended: true }));
app.use(express.static('client'));

/**
 * Returns the state of the emporium from MICE
 * No params
 */
app.get('/api/get_state', (req, res) => {
    getState(state => {
        res.send(state);
    });

});

/**
 * Create a container and register it to the state
 * send an object corresponding to a container in mice
 */
app.post('/api/create_container', (req, res) => {
    let body = req.body;
    MICE.createContainer(body);
    getState(state => {
        res.send(state);
    });
});

app.post('/api/create_scoop', (req, res) => {
    let body = req.body;
    MICE.createScoop(body);
    getState(state => {
        res.send(state);
    });
});

app.post('/api/create_topping', (req, res) => {
    let body = req.body;
    MICE.createTopping(body);
    getState(state => {
        res.send(state);
    });
});

app.post('/api/create_order', (req, res) => {

    let body = req.body;
    MICE.createOrder(body);
    getState(state => {
        res.send(state);
    });
});

// send an object with an id and status field example:
/*
{
    id: 2,
    status: "filled"
}
*/
app.post('/api/fill_order/:id', (req, res) => {
    let id = parseInt(req.params.id);

    MICE.fillOrder(id);

    getState(state => {
        res.send(state);
    });
});

/**
 * Create a server, a manager only function
 * send an object corresponding to the server obj
 */
app.post('/api/create_server', (req, res) => {
    let body = req.body;
    MICE.createServer(body);
    getState(state => {
        res.send(state);
    });
});

/**
 * Create a customer, a manager and server function
 * send an object corresponding to the customer obj
 */
app.post('/api/create_customer', (req, res) => {
    let body = req.body;
    MICE.createCustomer(body);
    getState(state => {
        res.send(state);
    });
});

app.post('/api/restock_item', (req, res) => {
    let body = req.body;

    console.log(body);
    switch (body.type) {
        case 'containers': {
            MICE.restockContainer(body);
        }
        case 'scoops': {
            MICE.restockScoop(body);
        }
        case 'toppings': {
            MICE.restockTopping(body);
        }
    }
    getState(state => {
        res.send(state);
    });
});

app.post('/api/fire_server', (req, res) => {
    let body = req.body;
    
});

app.get('/', (req, res) => {
    res.sendFile('./client/index.html');
});

// start the server
app.listen(PORT, () => {
    console.log(`Listening on port ${PORT}`);
});