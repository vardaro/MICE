#include <node.h>
#include <node_object_wrap.h>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

#include <v8.h>
#include <iostream>
#include <string>
#include <functional>

#include "container.h"
#include "emporium.h"
#include "order.h"
#include "server.h"
#include "customer.h"
#include "json.cpp"
#include <vector>

// this file exports CPP functions to the node server
using namespace v8;
using namespace std::placeholders;
// STATE MACHINE
// The current status of the emporium is stored in emporium STATE. every mutation on the client
// is sent to STATE where is applies the necessary mutation. once the state has been mutated, it gets recorded
// to the database, and a new copy of the STATE is sent to the client to be stored as a cookie...

emporium STATE;
// accepts the json of a container, creates a new container and apends to state
void createContainer(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    container c = unpackContainer(isolate, args);
    STATE.getContainers().emplace_back(c);
}

// creates a SCOOP
void createScoop(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    scoop c = unpackScoop(isolate, args);
    STATE.getScoops().emplace_back(c);
}

// creates a TOPPING
void createTopping(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    topping c = unpackTopping(isolate, args);
    STATE.getToppings().emplace_back(c);
}

// creates a order
void createOrder(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    order o = unpackOrder(isolate, args);

    // get a random number for order num
    srand(time(NULL));
    int rando = rand() % 10000 + 1; // random number between 0 and 10000

    o.setOrderNumber(rando);

    // STATE.getOrders().emplace_back(o);
    STATE.makeOrder(o);
}

// create a new server
void createServer(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    server s = unpackServer(isolate, args);
    STATE.getServers().emplace_back(s);
}

void fireServer(const v8::FunctionCallbackInfo<v8::Value> &args) {
    Isolate * isolate = args.GetIsolate();


    int indexOfServer = Local<Number>::Cast(args[0])->NumberValue();
    // EARSE THE SERVER FROM THE VECTOR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    STATE.getServers().erase(STATE.getServers().begin() + indexOfServer);
}

//  accepts an object container id and status, changes the status of the order at the id to the new status..
void fillOrder(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    int orderNumber = Handle<Value>::Cast(args[0])->NumberValue();

    STATE.getOrders()[orderNumber].setStatus("filled");
}

void createCustomer(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    customer c = unpackCustomer(isolate, args);
    STATE.getCustomers().emplace_back(c);
}

// TEMPLATE
// this template function returns a v8 array of a vector of objects
// if someone were to call vectorToArray<container>(isolate, std::bind(packFunction), std::bind(getFunction))
// the getFunction would get the vector from the STATE, and the pack function will get called at each iteration
// of the loop...
template <class templateType>
Local<Array> vectorToArray(Isolate *isolate, std::function<void(Isolate *, Local<Object>, templateType)> packFunction, std::function<std::vector<templateType>()> getFunction)
{
    Local<Array> newArray = Array::New(isolate);

    for (unsigned int i = 0; i < getFunction().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packFunction(isolate, result, getFunction()[i]);
        newArray->Set(i, result);
    }

    return newArray;
}

// returns a v8 array of the states containers
Local<Array> getStateContainers(Isolate *isolate)
{
    // pack container vector
    Local<Array> containerVec = Array::New(isolate);
    for (unsigned int i = 0; i < STATE.getContainers().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packContainer(isolate, result, STATE.getContainers()[i]);
        containerVec->Set(i, result);
    }
    return containerVec;
}

// returns a v8 array of the states scoops
Local<Array> getStateScoops(Isolate *isolate)
{
    // pack scoop vector
    Local<Array> scoopVec = Array::New(isolate);
    for (unsigned int i = 0; i < STATE.getScoops().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packScoop(isolate, result, STATE.getScoops()[i]);
        scoopVec->Set(i, result);
    }
    return scoopVec;
}

Local<Array> getStateToppings(Isolate *isolate)
{
    Local<Array> toppings = Array::New(isolate);
    for (unsigned int i = 0; i < STATE.getToppings().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packTopping(isolate, result, STATE.getToppings()[i]);
        toppings->Set(i, result);
    }
    return toppings;
}

// // TODO;
Local<Array> getStateOrders(Isolate *isolate)
{
    Local<Array> orders = Array::New(isolate);

    for (unsigned int i = 0; i < STATE.getOrders().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packOrder(isolate, result, STATE.getOrders()[i]);
        orders->Set(i, result);
    }

    return orders;
}

// // TODO;
Local<Array> getStateServers(Isolate *isolate)
{
    Local<Array> orders = Array::New(isolate);

    for (unsigned int i = 0; i < STATE.getServers().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packServer(isolate, result, STATE.getServers()[i]);
        orders->Set(i, result);
    }

    return orders;
}
// // TODO;
Local<Array> getStateCustomers(Isolate *isolate)
{
    Local<Array> orders = Array::New(isolate);

    for (unsigned int i = 0; i < STATE.getCustomers().size(); i++)
    {
        Local<Object> result = Object::New(isolate);
        packCustomer(isolate, result, STATE.getCustomers()[i]);
        orders->Set(i, result);
    }

    return orders;
}

// restock a container at a specified index by a specified amounts
void restockContainer(const v8::FunctionCallbackInfo<v8::Value> &args)
{

    // get the isolate, cast args to an object....
    // extract the index of the container and amount, then reassign the stock of that container
    Isolate *isolate = args.GetIsolate();
    Local<Object> body = Local<Object>::Cast(args[0]);
    int conIndex = Local<Number>::Cast(body->Get(String::NewFromUtf8(isolate, "index")))->NumberValue();
    int amountToStock = Local<Number>::Cast(body->Get(String::NewFromUtf8(isolate, "amount")))->NumberValue();
    STATE.getContainers()[conIndex].reassignStock(amountToStock);
}

void restockScoop(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();

    Local<Object> body = Local<Object>::Cast(args[0]);
    int conIndex = Local<Number>::Cast(body->Get(String::NewFromUtf8(isolate, "index")))->NumberValue();
    int amountToStock = Local<Number>::Cast(body->Get(String::NewFromUtf8(isolate, "amount")))->NumberValue();

    STATE.getScoops()[conIndex].reassignStock(amountToStock);
}

void restockTopping(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Object> body = Local<Object>::Cast(args[0]);
    int conIndex = Local<Number>::Cast(body->Get(String::NewFromUtf8(isolate, "index")))->NumberValue();
    int amountToStock = Local<Number>::Cast(body->Get(String::NewFromUtf8(isolate, "amount")))->NumberValue();

    STATE.getToppings()[conIndex].reassignStock(amountToStock);
}

// returns the current state of the emporium
void getState(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Object> newState = Object::New(isolate);

    // newState->Set(String::NewFromUtf8(isolate, "containers"), vectorToArray<container>(isolate, std::bind(&packContainer, _1, _2, _3), std::bind(&emporium::getContainers, &STATE)));
    // newState->Set(String::NewFromUtf8(isolate, "scoops"), vectorToArray<scoop>(isolate, std::bind(&packScoop, _1, _2, _3), std::bind(&emporium::getScoops, &STATE)));
    // newState->Set(String::NewFromUtf8(isolate, "toppings"), vectorToArray<topping>(isolate, std::bind(&packTopping, _1, _2, _3), std::bind(&emporium::getToppings, &STATE)));
    // newState->Set(String::NewFromUtf8(isolate, "orders"), vectorToArray<order>(isolate, std::bind(&packOrder, _1, _2, _3), std::bind(&emporium::getOrders, &STATE)));
    // newState->Set(String::NewFromUtf8(isolate, "servers"), vectorToArray<server>(isolate, std::bind(&packServer, _1, _2, _3), std::bind(&emporium::getServers, &STATE)));
    // newState->Set(String::NewFromUtf8(isolate, "customers"), vectorToArray<customer>(isolate, std::bind(&packCustomer, _1, _2, _3), std::bind(&emporium::getCustomers, &STATE)));
    newState->Set(String::NewFromUtf8(isolate, "containers"), getStateContainers(isolate));
    newState->Set(String::NewFromUtf8(isolate, "scoops"), getStateScoops(isolate));
    newState->Set(String::NewFromUtf8(isolate, "toppings"), getStateToppings(isolate));
    newState->Set(String::NewFromUtf8(isolate, "orders"), getStateOrders(isolate));
    newState->Set(String::NewFromUtf8(isolate, "servers"), getStateServers(isolate));
    newState->Set(String::NewFromUtf8(isolate, "customers"), getStateCustomers(isolate));
    newState->Set(String::NewFromUtf8(isolate, "cash_register"), Number::New(isolate, STATE.getCashRegister().getBalance()));

    args.GetReturnValue().Set(newState);
}

void loadState(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Local<Object> state = Local<Object>::Cast(args[0]);

    // LOAD ALL THE DATA INTO THE STATE.....
    // TODO make it a tmeplate function.............
    Local<Array> containerArr = Local<Array>::Cast(state->Get(String::NewFromUtf8(isolate, "containers")));
    for (unsigned int i = 0; i < containerArr->Length(); i++)
    {
        Handle<Object> cur = Handle<Object>::Cast(containerArr->Get(i));
        container c = unpackContainer(isolate, cur);
        STATE.getContainers().emplace_back(c);
    }
    Local<Array> scoopArr = Local<Array>::Cast(state->Get(String::NewFromUtf8(isolate, "scoops")));
    for (unsigned int i = 0; i < scoopArr->Length(); i++)
    {
        Handle<Object> cur = Handle<Object>::Cast(scoopArr->Get(i));
        scoop c = unpackScoop(isolate, cur);
        STATE.getScoops().emplace_back(c);
    }
    Local<Array> toppingArr = Local<Array>::Cast(state->Get(String::NewFromUtf8(isolate, "toppings")));
    for (unsigned int i = 0; i < toppingArr->Length(); i++)
    {
        Handle<Object> cur = Handle<Object>::Cast(toppingArr->Get(i));
        topping c = unpackTopping(isolate, cur);
        STATE.getToppings().emplace_back(c);
    }
    Local<Array> orderArr = Local<Array>::Cast(state->Get(String::NewFromUtf8(isolate, "orders")));
    for (unsigned int i = 0; i < orderArr->Length(); i++)
    {
        Handle<Object> cur = Handle<Object>::Cast(orderArr->Get(i));
        order o = unpackOrder(isolate, cur);
        STATE.getOrders().emplace_back(o);
    }
    Local<Array> serverArr = Local<Array>::Cast(state->Get(String::NewFromUtf8(isolate, "servers")));
    for (unsigned int i = 0; i < serverArr->Length(); i++)
    {
        Handle<Object> cur = Handle<Object>::Cast(serverArr->Get(i));
        server o = unpackServer(isolate, cur);
        STATE.getServers().emplace_back(o);
    }
    Local<Array> customerArr = Local<Array>::Cast(state->Get(String::NewFromUtf8(isolate, "customers")));
    for (unsigned int i = 0; i < customerArr->Length(); i++)
    {
        Handle<Object> cur = Handle<Object>::Cast(customerArr->Get(i));
        customer o = unpackCustomer(isolate, cur);
        STATE.getCustomers().emplace_back(o);
    }
    Local<Number> cashRegister = Local<Number>::Cast(state->Get(String::NewFromUtf8(isolate, "cash_register")));
    STATE.getCashRegister().applyBalance(cashRegister->NumberValue());
    //finally done with that....
}

void init(Handle<Object> exports, Handle<Object> module)
{
    STATE.initCashRegister(0.0);

    NODE_SET_METHOD(exports, "createContainer", createContainer);
    NODE_SET_METHOD(exports, "createScoop", createScoop);
    NODE_SET_METHOD(exports, "createTopping", createTopping);
    NODE_SET_METHOD(exports, "createOrder", createOrder);
    NODE_SET_METHOD(exports, "fillOrder", fillOrder);
    NODE_SET_METHOD(exports, "createServer", createServer);
    NODE_SET_METHOD(exports, "createCustomer", createCustomer);
    NODE_SET_METHOD(exports, "restockContainer", restockContainer);
    NODE_SET_METHOD(exports, "restockScoop", restockScoop);
    NODE_SET_METHOD(exports, "restockTopping", restockTopping);

    NODE_SET_METHOD(exports, "getState", getState);
    NODE_SET_METHOD(exports, "loadState", loadState);
}

NODE_MODULE(mice, init)