#include <v8.h>
#include <node.h>
#include <vector>

using namespace v8;

// This file is for parsing and building json to be sent to and from node

// POLYMORPHISM

// two functions named unpackContainer, both serve the same purpoe of unpack json, but take different params
container unpackContainer(Isolate *isolate, const v8::FunctionCallbackInfo<v8::Value> &args)
{
    Handle<Object> containerObj = Handle<Object>::Cast(args[0]);

    // parse the json...
    v8::String::Utf8Value name(containerObj->Get(String::NewFromUtf8(isolate, "name")));
    v8::String::Utf8Value desc(containerObj->Get(String::NewFromUtf8(isolate, "description")));
    double wholesaleCost = containerObj->Get(String::NewFromUtf8(isolate, "wholesaleCost"))->NumberValue();
    double retailCost = containerObj->Get(String::NewFromUtf8(isolate, "retailCost"))->NumberValue();
    int stock = containerObj->Get(String::NewFromUtf8(isolate, "stockRemaining"))->NumberValue();
    v8::String::Utf8Value img(containerObj->Get(String::NewFromUtf8(isolate, "img")));
    int scoopCount = containerObj->Get(String::NewFromUtf8(isolate, "scoopCount"))->NumberValue();

    //fially make the contaienr object
    container c(std::string(*name), std::string(*desc), wholesaleCost, retailCost, stock, std::string(*img), scoopCount);
    return c;
}

container unpackContainer(Isolate * isolate, const Handle<Object> containerObj) {
    // parse the json...
    v8::String::Utf8Value name(containerObj->Get(String::NewFromUtf8(isolate, "name")));
    v8::String::Utf8Value desc(containerObj->Get(String::NewFromUtf8(isolate, "description")));
    double wholesaleCost = containerObj->Get(String::NewFromUtf8(isolate, "wholesaleCost"))->NumberValue();
    double retailCost = containerObj->Get(String::NewFromUtf8(isolate, "retailCost"))->NumberValue();
    int stock = containerObj->Get(String::NewFromUtf8(isolate, "stockRemaining"))->NumberValue();
    v8::String::Utf8Value img(containerObj->Get(String::NewFromUtf8(isolate, "img")));
    int scoopCount = containerObj->Get(String::NewFromUtf8(isolate, "scoopCount"))->NumberValue();

    //fially make the contaienr object
    container c(std::string(*name), std::string(*desc), wholesaleCost, retailCost, stock, std::string(*img), scoopCount);
    return c;
}

// packs a container object cur into a v8 object obj
void packContainer(Isolate* isolate, Local<Object> & obj, container cur)
{
    // now start building that json object.....
    obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, cur.getName().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "description"), String::NewFromUtf8(isolate, cur.getDescription().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "wholesaleCost"), Number::New(isolate, cur.getWholesaleCost()));
    obj->Set(String::NewFromUtf8(isolate, "retailCost"), Number::New(isolate, cur.getRetailCost()));
    obj->Set(String::NewFromUtf8(isolate, "stockRemaining"), Number::New(isolate, cur.getStockRemaining()));
    obj->Set(String::NewFromUtf8(isolate, "img"), String::NewFromUtf8(isolate, cur.getImg().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "scoopCount"), Number::New(isolate, cur.getScoopCount()));

}

// POLYMORPHISM 

// another instance of fuction overloading  with unpackScoop
// unpack json object of a scoop
scoop unpackScoop(Isolate * isolate, const v8::FunctionCallbackInfo<v8::Value> & args) {
    Handle<Object> scoopObj = Handle<Object>::Cast(args[0]);

    v8::String::Utf8Value name(scoopObj->Get(String::NewFromUtf8(isolate, "name")));
    v8::String::Utf8Value desc(scoopObj->Get(String::NewFromUtf8(isolate, "description")));
    double wholesaleCost = scoopObj->Get(String::NewFromUtf8(isolate, "wholesaleCost"))->NumberValue();
    double retailCost = scoopObj->Get(String::NewFromUtf8(isolate, "retailCost"))->NumberValue();
    int stock = scoopObj->Get(String::NewFromUtf8(isolate, "stockRemaining"))->NumberValue();
    v8::String::Utf8Value img(scoopObj->Get(String::NewFromUtf8(isolate, "img")));

    scoop s(std::string(*name), std::string(*desc), wholesaleCost, retailCost, stock, std::string(*img));
    return s;
}

scoop unpackScoop(Isolate * isolate, const Handle<Object> scoopObj) {
    v8::String::Utf8Value name(scoopObj->Get(String::NewFromUtf8(isolate, "name")));
    v8::String::Utf8Value desc(scoopObj->Get(String::NewFromUtf8(isolate, "description")));
    double wholesaleCost = scoopObj->Get(String::NewFromUtf8(isolate, "wholesaleCost"))->NumberValue();
    double retailCost = scoopObj->Get(String::NewFromUtf8(isolate, "retailCost"))->NumberValue();
    int stock = scoopObj->Get(String::NewFromUtf8(isolate, "stockRemaining"))->NumberValue();
    v8::String::Utf8Value img(scoopObj->Get(String::NewFromUtf8(isolate, "img")));

    //fially make the contaienr object
    scoop c(std::string(*name), std::string(*desc), wholesaleCost, retailCost, stock, std::string(*img));
    return c;
}

// packs scoop cur into obj to be sent to node
void packScoop(Isolate * isolate, Local<Object> & obj, scoop cur) {
    obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, cur.getName().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "description"), String::NewFromUtf8(isolate, cur.getDescription().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "wholesaleCost"), Number::New(isolate, cur.getWholesaleCost()));
    obj->Set(String::NewFromUtf8(isolate, "retailCost"), Number::New(isolate, cur.getRetailCost()));
    obj->Set(String::NewFromUtf8(isolate, "stockRemaining"), Number::New(isolate, cur.getStockRemaining()));
    obj->Set(String::NewFromUtf8(isolate, "img"), String::NewFromUtf8(isolate, cur.getImg().c_str()));
}

// POLYMORPHISM

// Same kind of polymoorsphim above... two functions that both unpack json but with different signatures

// unpack json object of a scoop
topping unpackTopping(Isolate * isolate, const v8::FunctionCallbackInfo<v8::Value> & args) {
    Handle<Object> toppingObj = Handle<Object>::Cast(args[0]);

    v8::String::Utf8Value name(toppingObj->Get(String::NewFromUtf8(isolate, "name")));
    v8::String::Utf8Value desc(toppingObj->Get(String::NewFromUtf8(isolate, "description")));
    double wholesaleCost = toppingObj->Get(String::NewFromUtf8(isolate, "wholesaleCost"))->NumberValue();
    double retailCost = toppingObj->Get(String::NewFromUtf8(isolate, "retailCost"))->NumberValue();
    int stock = toppingObj->Get(String::NewFromUtf8(isolate, "stockRemaining"))->NumberValue();
    v8::String::Utf8Value img(toppingObj->Get(String::NewFromUtf8(isolate, "img")));

    topping s(std::string(*name), std::string(*desc), wholesaleCost, retailCost, stock, std::string(*img));
    return s;
}

topping unpackTopping(Isolate * isolate, const Handle<Object> toppingObj) {
    v8::String::Utf8Value name(toppingObj->Get(String::NewFromUtf8(isolate, "name")));
    v8::String::Utf8Value desc(toppingObj->Get(String::NewFromUtf8(isolate, "description")));
    double wholesaleCost = toppingObj->Get(String::NewFromUtf8(isolate, "wholesaleCost"))->NumberValue();
    double retailCost = toppingObj->Get(String::NewFromUtf8(isolate, "retailCost"))->NumberValue();
    int stock = toppingObj->Get(String::NewFromUtf8(isolate, "stockRemaining"))->NumberValue();
    v8::String::Utf8Value img(toppingObj->Get(String::NewFromUtf8(isolate, "img")));

    //fially make the contaienr object
    topping c(std::string(*name), std::string(*desc), wholesaleCost, retailCost, stock, std::string(*img));
    return c;
}

// packs scoop cur into obj to be sent to node
// obj is the object that gets data packed into, cur is a topping from which we get the original data
void packTopping(Isolate * isolate, Local<Object> & obj, topping cur) {
    obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, cur.getName().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "description"), String::NewFromUtf8(isolate, cur.getDescription().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "wholesaleCost"), Number::New(isolate, cur.getWholesaleCost()));
    obj->Set(String::NewFromUtf8(isolate, "retailCost"), Number::New(isolate, cur.getRetailCost()));
    obj->Set(String::NewFromUtf8(isolate, "stockRemaining"), Number::New(isolate, cur.getStockRemaining()));
    obj->Set(String::NewFromUtf8(isolate, "img"), String::NewFromUtf8(isolate, cur.getImg().c_str()));
}

serving unpackServing(Isolate * isolate, const Handle<Object> servingObj){
    // holy shit...
    // extract and unpack the container object
    Handle<Object> containerAsAnObject = Handle<Object>::Cast(servingObj->Get(String::NewFromUtf8(isolate, "container")));
    container servingContainer = unpackContainer(isolate, containerAsAnObject);
    int containerIndex = (int)servingObj->Get(String::NewFromUtf8(isolate, "containerIndex"))->IntegerValue();

    Handle<Array> scoopArr = Handle<Array>::Cast(servingObj->Get(String::NewFromUtf8(isolate, "scoops")));
    Handle<Array> scoopIndexes = Handle<Array>::Cast(servingObj->Get(String::NewFromUtf8(isolate, "scoopIndexes")));

    std::vector<scoop> scoopVector = {};
    std::vector<int> scoopIndexVector = {};
    // iterate over the v8 array of scoops, cast each index as a v8 object and parse the json
    // then push to the scoop vector
    int scoopCount = scoopArr->Length();
    for (int i = 0; i < scoopCount; i++) {
        Handle<Object> scoopAsAnObject = Handle<Object>::Cast(scoopArr->Get(i));
        scoop s = unpackScoop(isolate, scoopAsAnObject);
        scoopVector.emplace_back(s);

        // while in the loop might as well push the index of the current scoop to the scoop index vector
        scoopIndexVector.emplace_back((int)scoopIndexes->Get(i)->IntegerValue());
    }

    // do the same for the number of toppings, iterate over topping objects and push them to a vector after
    // unpackig it
    Handle<Array> toppingArr = Handle<Array>::Cast(servingObj->Get(String::NewFromUtf8(isolate, "toppings")));
    Handle<Array> toppingIndexes = Handle<Array>::Cast(servingObj->Get(String::NewFromUtf8(isolate, "toppingIndexes")));
    
    std::vector<topping> toppingVector = {};
    std::vector<int> toppingIndexVector = {};
    int toppingCount = toppingArr->Length();
    for (int i = 0; i < toppingCount; i++) {
        Handle<Object> toppingAsAnObject = Handle<Object>::Cast(toppingArr->Get(i));
        topping t = unpackTopping(isolate, toppingAsAnObject);
        toppingVector.emplace_back(t);

        toppingIndexVector.emplace_back((int)toppingIndexes->Get(i)->IntegerValue());
    }

    serving s(servingContainer, containerIndex, scoopVector, scoopIndexVector, toppingVector, toppingIndexVector);
    return s;
}

order unpackOrder(Isolate * isolate, Handle<Object> orderObject) {
    // extract the status of the obj
    v8::String::Utf8Value status(orderObject->Get(String::NewFromUtf8(isolate, "status")));
    Handle<Number> orderNumber = Handle<Number>::Cast(orderObject->Get(String::NewFromUtf8(isolate, "orderNumber")));

    // get teh samples
    std::vector<serving> servingVector;
    // cast the serving array as a v8 array
    Handle<Array> servingArr = Handle<Array>::Cast(orderObject->Get(String::NewFromUtf8(isolate, "servings")));

    // get the length and iterate over
    int servingCount = servingArr->Length();
    for (int i = 0; i < servingCount; i++) {
        // unpack the current iteration, store it in s, and push it to the vector
        serving s = unpackServing(isolate, Handle<Object>::Cast(servingArr->Get(i)));
        servingVector.emplace_back(s);
    }

    // make the final object
    order s(std::string(*status), servingVector);
    s.setOrderNumber(orderNumber->NumberValue());
    return s;
}

// Take a FunctionCallbackInfo, casts is as an object and unpacks all the servings of that object
order unpackOrder(Isolate * isolate, const v8::FunctionCallbackInfo<v8::Value> & args){
    Handle<Object> orderObject = Handle<Object>::Cast(args[0]);

    return unpackOrder(isolate, orderObject);
}


// // packs scoop cur into obj to be sent to node
void packOrder(Isolate * isolate, Local<Object> & obj, order cur) {

    // pack status
    obj->Set(String::NewFromUtf8(isolate, "status"), String::NewFromUtf8(isolate, cur.getStatus().c_str()));
    // pack the ordernumber along with it
    obj->Set(String::NewFromUtf8(isolate, "orderNumber"), Number::New(isolate, cur.getOrderNumber()));
    //... and the price...
    obj->Set(String::NewFromUtf8(isolate, "totalPrice"), Number::New(isolate, cur.getTotalCost()));

    Local<Array> servingArr = Array::New(isolate);

    // populate serving vector
    int len = cur.getServings().size();

    // iterate over the servings in the order......
    for (int i = 0; i < len; i++) {
        // the final packed object that gets set to the v8 array
        Local<Object> result = Object::New(isolate);

        // pack the container
        Local<Object> packedContainerTarget = Object::New(isolate);
        packContainer(isolate, packedContainerTarget, cur.getServings()[i].getContainer());
        result->Set(String::NewFromUtf8(isolate, "container"), packedContainerTarget);        

        // pack the price...
        result->Set(String::NewFromUtf8(isolate, "price"), Number::New(isolate, cur.getServings()[i].getPrice()));

        // pack the scoops
        Local<Array> packedScoopsArray = Array::New(isolate);
        int curServingScoopAmount = cur.getServings()[i].getScoops().size();
        // iterate over the scoops, pack each scoop intro packedScoopsArray...
        for (int j = 0; j < curServingScoopAmount; j++) {
            // init new v8 object ughhh
            Local<Object> scoopTarget = Object::New(isolate);
            
            packScoop(isolate, scoopTarget, cur.getServings()[i].getScoops()[j]);
            packedScoopsArray->Set(j, scoopTarget);
        }
        // now that we create the v8 array of scoops...
        // apply it to the v8 result object
        result->Set(String::NewFromUtf8(isolate, "scoops"), packedScoopsArray);        

        // Now do the EXACT same operation on the servings toppings...........
        Local<Array> packedToppingsArray = Array::New(isolate);
        int curServingToppingAmount = cur.getServings()[i].getToppings().size();

        // iterate over the scoops, pack each scoop intro packedScoopsArray...
        for (int j = 0; j < curServingToppingAmount; j++) {
            // init new v8 object ughhh
            Local<Object> toppingTarget = Object::New(isolate);
            packTopping(isolate, toppingTarget, cur.getServings()[i].getToppings()[j]);
            packedToppingsArray->Set(j, toppingTarget);
        }
        // finally we can append the v8 array to the final object
        result->Set(String::NewFromUtf8(isolate, "toppings"), packedToppingsArray);
        
        // finally set the packed serving to the array :) ......
        servingArr->Set(i, result);
    }
    obj->Set(String::NewFromUtf8(isolate, "servings"), servingArr);
        
}

server unpackServer(Isolate * isolate, Handle<Object> serverObj) {
    v8::String::Utf8Value name(serverObj->Get(String::NewFromUtf8(isolate, "name")));
    int id = serverObj->Get(String::NewFromUtf8(isolate, "employeeID"))->NumberValue();
    double wage = serverObj->Get(String::NewFromUtf8(isolate, "employeeID"))->NumberValue();
    
    return server(std::string(*name), id, wage);
}

server unpackServer(Isolate * isolate, const v8::FunctionCallbackInfo<v8::Value> & args) {
    Handle<Object> serverObj = Handle<Object>::Cast(args[0]);
    
    return unpackServer(isolate, serverObj);
}

void packServer(Isolate * isolate, Local<Object> & obj, server cur) {
    obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, cur.getName().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "employeeID"), Number::New(isolate, cur.getEmployeeID()));
    obj->Set(String::NewFromUtf8(isolate, "numOrders"), Number::New(isolate, cur.getNumOrders()));
    obj->Set(String::NewFromUtf8(isolate, "wage"), Number::New(isolate, cur.getWage()));
}

customer unpackCustomer(Isolate * isolate, Handle<Object> cus) {
    v8::String::Utf8Value name(cus->Get(String::NewFromUtf8(isolate, "name")));
    int id = cus->Get(String::NewFromUtf8(isolate, "customerID"))->NumberValue();
    int phone = cus->Get(String::NewFromUtf8(isolate, "phoneNumber"))->NumberValue();

    return customer(std::string(*name), phone, id);
}

customer unpackCustomer(Isolate * isolate, const v8::FunctionCallbackInfo<v8::Value> & args) {
    Handle<Object> cus = Handle<Object>::Cast(args[0]);

    return unpackCustomer(isolate, cus);
}

void packCustomer(Isolate * isolate, Local<Object> & obj, customer cur) {

    obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, cur.getName().c_str()));
    obj->Set(String::NewFromUtf8(isolate, "employeeID"), Number::New(isolate, cur.getCustomerID()));
    obj->Set(String::NewFromUtf8(isolate, "phoneNumber"), Number::New(isolate, cur.getPhoneNumber()));
}
