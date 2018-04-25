#include <node.h>
#include <node_object_wrap.h>

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
    o.setOrderNumber(STATE.getOrders().size()); // set the order number to the index lol

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

//  accepts an object container id and status, changes the status of the order at the id to the new status..
void changeOrderStatus(const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Isolate *isolate = args.GetIsolate();
    Handle<Object> object = Handle<Object>::Cast(args[0]);

    int orderNumber = object->Get(String::NewFromUtf8(isolate, "id"))->NumberValue();
    v8::String::Utf8Value status(object->Get(String::NewFromUtf8(isolate, "status")));

    STATE.getOrders()[orderNumber].setStatus(std::string(*status));
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

    //finally done with that.... 
}

void init(Handle<Object> exports, Handle<Object> module)
{
    NODE_SET_METHOD(exports, "createContainer", createContainer);
    NODE_SET_METHOD(exports, "createScoop", createScoop);
    NODE_SET_METHOD(exports, "createTopping", createTopping);
    NODE_SET_METHOD(exports, "createOrder", createOrder);
    NODE_SET_METHOD(exports, "changeOrderStatus", changeOrderStatus);
    NODE_SET_METHOD(exports, "createServer", createServer);
    NODE_SET_METHOD(exports, "createCustomer", createCustomer);

    NODE_SET_METHOD(exports, "getState", getState);
    NODE_SET_METHOD(exports, "loadState", loadState);
}

NODE_MODULE(mice, init)