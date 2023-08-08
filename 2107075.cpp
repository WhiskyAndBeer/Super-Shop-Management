#include<bits/stdc++.h>
#include<conio.h>

using namespace std;

class Product;
class Customer_Cart;
class Customer;
class Cashier;
class Office;
class Stock;
class SuperMarket;

class Product {
    int id, quantity;
    double price;
    string name, category;
    bool is_available;
public:
    Product() { ; }
    Product(int id, double price, int quantity, string name, string category, bool is_available) {
        this->id = id;
        this->price = price;
        this->quantity = quantity;
        this->name = name;
        this->category = category;
        this->is_available = is_available;
    }
    void Product_setter(int id, double price, int quantity, string name, string category, bool is_available) {
        this->id = id;
        this->price = price;
        this->quantity = quantity;
        this->name = name;
        this->category = category;
        this->is_available = is_available;
    }
    void Product_getter() {
        cout<<endl;
        cout << "Product ID: " << this->id << endl;
        cout << "Product Name: " << this->name << endl;
        cout << "Product Price: " << this->price << endl;
        cout << "Product Quantity: " << this->quantity << endl;
        cout << "Product Category: " << this->category << endl;
        cout << "Product Availability: " << ((this->is_available) ? "Available" : "Not Available") << endl;
    }
    string name_getter() {
        return name;
    }
    bool product_avail() const {
        return is_available;
    }
    int id_getter() const {
        return id;
    }
    int quant_getter() const {
        return quantity;
    }
    void set_quant(int i) {
        quantity = i;
    }
    void set_avail(int i){
        if(i<=0){
            is_available=0;
        }
        else{
            is_available=1;
        }
    }
    double price_getter() const {
        return price;
    }
    string category_getter() {
        return category;
    }
    ~Product(){;}
};

class Customer_Cart {
    vector<Product>products;
    int tot_prod;
    double total_price;
public:
    Customer_Cart() { total_price = 0; tot_prod = 0; }
    void show_cart();
    void add_to_cart(const Product&, int);
    bool remove_from_cart(const Product&, int);
    double total_price_calc() {
        return total_price;
    }
    friend class Cashier;
    friend bool operator==(Product&, Product&);
    int get_prod() {
        return tot_prod;
    }
    void removeall(){
        products.clear();
        tot_prod=0;
        total_price=0;
    }
    ~Customer_Cart(){;}
};

bool operator==(const Product& p, const Product& q) {
    if (p.id_getter() == q.id_getter()) {
        return true;
    }
    return false;
}

void Customer_Cart::show_cart() {
    cout<<"________________________________________\v";
    for (int i = 0; i < tot_prod; i++) {
        cout<<endl;
        products[i].Product_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}

void Customer_Cart::add_to_cart(const Product& p, int q) {
    products.push_back(p);
    products.at(products.size() - 1).set_quant(q);
    total_price += (products.at(products.size() - 1).price_getter() * q);
    tot_prod++;
}
bool Customer_Cart::remove_from_cart(const Product& p, int q) {
    int i;
    for (i = 0; i < tot_prod; i++) {
        if (products[i] == p) {
            break;
        }
    }
    if(i>=tot_prod){
        cout<<"You don't have this product in your cart yet"<<endl;
        return false;
    }
    else{
        auto it = products.begin();
        it += i;
        if (products[i].quant_getter() <= q) {
            products.erase(it);
            tot_prod--;
        }
        else {
            products[i].set_quant(products[i].quant_getter() - q);
        }
        total_price -= (p.price_getter() * q);
        return true;
    }
}

class Stock {
    vector<Product>products;
    int total_products;
    int total_avail_products;
public:
    Stock() { total_products = 0; total_avail_products=0; }
    void show_product();
    void show_avail();
    Product& prod_return(int);
    bool if_avail(int, int);
    void add_product(const Product& product);
    void remove_product(const Product& product, int);
    void update_quantity(const Product& product, int quantity);
    void restock(const Product&);
    friend bool operator==(Product&, Product&);
    void search_product(int);
    void search_product(string);
    void search_product(string,int);
    void search_product(double,double);
    ~Stock(){;}
};

void Stock::add_product(const Product& product) {
    products.push_back(product);
    total_products++;
    if((products.at(products.size()-1).product_avail())){
        total_avail_products++;
    }
}

void Stock::remove_product(const Product& product, int quantity) {
    int i;
    for (i = 0; i < total_products; i++) {
        if (products[i] == product) {
            break;
        }
    }
    if (products[i].quant_getter() <= quantity) {
        products[i].set_quant(0);
        products[i].set_avail(products[i].quant_getter() - quantity);
        total_avail_products--;
    }
    else {
        products[i].set_quant(products[i].quant_getter() - quantity);
    }
}

void Stock::restock(const Product& p){
    int i;
    for (i = 0; i < total_products; i++) {
        if (products[i] == p) {
            products[i].set_quant(1);
            products[i].set_avail(1);
            total_avail_products++;
        }
    }
}


void Stock::show_product() {
    int n = products.size();
    cout<<"________________________________________\v";
    cout<<"There are total "<<total_avail_products<<" products in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<endl;
        products[i].Product_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}
void Stock::show_avail() {
    int n = products.size();
    cout<<"________________________________________\v";
    cout<<"There are "<<total_avail_products<<" products currently available in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        if (products[i].product_avail() == 1) {
            cout<<endl;
            products[i].Product_getter();
            cout << endl;
        }
    }
    cout<<"________________________________________\v"<<endl;
}

bool Stock::if_avail(int id, int quantity) {
    int n = products.size();
    for (int i = 0; i < n; i++) {
        if (products[i].id_getter() == id) {
            if (products[i].product_avail() == 1) {
                if (products[i].quant_getter() >= quantity) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Stock::update_quantity(const Product& product, int quantity) {
    int i;
    for (i = 0; i < total_products; i++) {
        if (products[i] == product) {
            products.at(i).set_quant(quantity + products[i].quant_getter());
            break;
        }
    }
    if (i >= total_products) {
        products.push_back(product);
        products.at(products.size() - 1).set_quant(quantity);
        total_products++;
    }
}

Product& Stock::prod_return(int id) {
    int n = products.size();
    for (int i = 0; i < n; i++) {
        if (products[i].id_getter() == id) {
            return products[i];
        }
    }
    return products[0];
}

void Stock::search_product(int id){
    int i;
    cout<<"\n=========================================================================\v"<<endl;
    for(i=0;i<total_products;i++){
        if(products[i].id_getter()==id){
            cout<<"Your desired product has been found in our shop"<<endl<<endl;
            cout<<"The product is "<<((products[i].product_avail())?"available":"not available")<<endl<<endl;
            products[i].Product_getter();
        }
    }
    if(i>=total_products){
        cout<<"The product is not currently available in our store"<<endl<<endl;
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Stock::search_product(string name){
    int i;
    cout<<"\n=========================================================================\v"<<endl;
    for(i=0;i<total_products;i++){
        if(products[i].name_getter()==name){
            cout<<"Your desired product has been found in our shop"<<endl<<endl;
            cout<<"The product is "<<((products[i].product_avail())?"available":"not available")<<endl<<endl;
            products[i].Product_getter();
        }
    }
    if(i>=total_products){
        cout<<"The product is not currently available in our store"<<endl<<endl;
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Stock::search_product(string category,int dummy){
    int i,count=0;
    for(i=0;i<total_products;i++){
        if(products[i].category_getter()==category){
            count++;
        }
    }
    if(count==0){
        cout<<"There are no products available in that category."<<endl<<endl;
        return;
    }
    cout<<"=========================================================================\v"<<endl;
    cout<<"\n\nThere are "<<count<<" products available in this category\v"<<endl;
    for(i=0;i<total_products;i++){
        if(products[i].category_getter()==category){
            products[i].Product_getter();
        }
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Stock::search_product(double low, double high){
    int i,price,count=0;
    for(i=0;i<total_products;i++){
        price=products[i].price_getter();
        if(price>=low && price <=high){
            count++;
        }
    }
    if(count==0){
        cout<<"There are no products available in the current price range"<<endl<<endl;
        return;
    }
    cout<<"=========================================================================\v"<<endl;
    cout<<"\n\nThere are "<<count<<" products available in this price range\v"<<endl;
    for(i=0;i<total_products;i++){
        price=products[i].price_getter();
        if(price>=low && price <=high){
            products[i].Product_getter();
        }
    }
    cout<<"\n=========================================================================\v"<<endl;
}


class Customer {
    int id;
    bool exclusive;
    string name, address, contact_num, email, gender;
    double net_spent;
public:
    Customer() { exclusive=0; net_spent=0;}
    Customer(int id, string name, string address, string contact_num, string email, string gender) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->contact_num = contact_num;
        this->email = email;
        this->gender = gender;
        this->exclusive=0;
    }
    string get_name() {
        return this->name;
    }
    string get_gender() {
        return this->gender;
    }
    int get_id(){
        return this->id;
    }
    bool exclusive_getter(){
        return this->exclusive;
    }
    void set_exlusive(){
        this->exclusive=true;
    }
    void set_spent(double spent){
        this->net_spent+=spent;
    }
    void cust_getter() {
        cout<<endl;
        cout << "Customer Id: " << id << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Customer address: " << address << endl;
        cout << "Customer Contact Number: " << contact_num << endl;
        cout << "Customer Email: " << email << endl;
        cout << "Customer Gender: " << gender << endl;
        cout << "Customer Total spent: "<< net_spent<<endl;
    }
    ~Customer(){;}
};


class Cashier {
    int id;
    string name;
public:
    Cashier() { ; }
    Cashier(int id, string name) {
        this->id = id;
        this->name = name;
    }
    void process_payment(Customer_Cart&, Customer&);
    string getname() {
        return this->name;
    }
    int getid(){
        return this->id;
    }
    void cashier_getter(){
        cout<<endl;
        cout << "Cashier ID: " << this->id << endl;
        cout << "Cashier Name: " << this->name << endl;
    }
    ~Cashier(){;}

};

void Cashier::process_payment(Customer_Cart& cart, Customer& customer) {
    double tot=0;
    if(customer.exclusive_getter()){
        cout<<"\n\n\n Congratulations!!! You have got the exclusive membership in this shop. You will get 20% discount in your current and next purchases!!!\n\n\n";
    }
    cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "|========================================SUPERSHOP PAYMENT RECEIPT========================================|" << endl;
    cout<<"---------------------------------------------------------------------------------------------------------------\v"<<endl;
    cout << "CONTACT INFO:\v"<<endl;
    customer.cust_getter();
    cout << "==========================================================================================================\v" << endl;
    cout << "Cashier ID: " << id << endl;
    cout << "Cashier: " << name << endl;
    cout << "==========================================================================================================\v" << endl;
    cout << "SERIAL NO.               ITEM               QUANTITY               CATEGORY               PRICE\v";

    for (int i = 0; i < cart.tot_prod; i++) {
        cout <<"    "<<(i + 1);
        cout<< "                  " << cart.products[i].name_getter();
        cout<< "               " << cart.products[i].quant_getter();
        cout<< "                  " << cart.products[i].category_getter();
        cout<< "              " << cart.products[i].price_getter() << endl << endl;
    }
    cout << "__________________________________________________________________________________________________" << endl << endl;
    cout << "TOTAL PRICE                                                                              " << cart.total_price_calc() << endl << endl;
    cout << "VAT                                                                                      " << (cart.total_price_calc() * 0.15) << endl << endl;
    if(customer.exclusive_getter()){
        cout << "__________________________________________________________________________________________________" << endl << endl;
        cout <<"DISCOUNT                                                                                -"<< (cart.total_price_calc()+ cart.total_price_calc() * 0.15)*0.2 <<endl <<endl;
        cout << "__________________________________________________________________________________________________" << endl << endl;
        tot = (cart.total_price_calc() + (cart.total_price_calc() * 0.15))*0.8;
        cout << "GRAND TOTAL                                                                              " <<  tot << "\v";
    }
    else{
        cout << "__________________________________________________________________________________________________" << endl << endl;
        tot = cart.total_price_calc() + (cart.total_price_calc() * 0.15);
        cout << "GRAND TOTAL                                                                              " << tot << "\v";
    }
    cout << "\v";
    customer.set_spent(tot);
    if(tot>=1000){
        if(!customer.exclusive_getter()){
            cout<<"\nCongratulations, you are now an exlusive member of this shop. Come back again to enjoy a flat 20% discount on your next purchase!!!\n\n";
        }
        customer.set_exlusive();
    }
    cout << "Thank you for choosing us " << ((customer.get_gender() == "Male") ? " Sir" : " Madam") << ". Come visit us again\v";

    cout << "\v===========================SUPERSHOP MANAGEMENT SYSTEM BY SARWAD========================================\v" << endl;
}

class Office{
    vector<Cashier>cashier;
    int total_employees;
    public:
        Office(){total_employees=0;}
        void add_cashier(const Cashier&);
        void remove_cashier(int);
        void show_cashiers();
        Cashier get_cashier(int);
        ~Office(){;}
};

Cashier Office::get_cashier(int id){
    for(int i = 0;i<total_employees;i++){
        if(cashier[i].getid()==id){
            return cashier[i];
        }
    }
    return cashier[0];
}

void Office::add_cashier(const Cashier& c){
    cashier.push_back(c);
    total_employees++;
}

void Office::remove_cashier(int id){
    int i;
    for (i = 0; i < total_employees; i++) {
        if ((cashier[i].getid())==id) {
            break;
        }
    }
    if(i>=total_employees){
        cout<<"There aren't any employee with that id here"<<endl;
    }
    else{
        auto it = cashier.begin();
        it += i;
        cashier.erase(it);
        total_employees--;
    }
}

void Office::show_cashiers(){
    int n = cashier.size();
    cout<<"________________________________________\v";
    cout<<"There are total "<<total_employees<<" employees in the shop\v"<<endl;
    for (int i = 0; i < n; i++) {
        cout<<endl;
        cashier[i].cashier_getter();
        cout << endl;
    }
    cout<<"________________________________________\v"<<endl;
}

class Database{
    vector<Customer>customers;
    int total_customers;
    public:
        Database(){total_customers=0;}
        void add_customers(const Customer&);
        bool find_customers(int);
        Customer& customer_getter(int);
        void show_all();
        ~Database(){;}

};

void Database::show_all(){
    cout<<"\n=========================================================================\v"<<endl;
    cout<<"Total of "<<total_customers<<" customers have visited this shop"<<endl;
    for(int i = 0;i<total_customers;i++){
        customers[i].cust_getter();
    }
    cout<<"\n=========================================================================\v"<<endl;
}

void Database::add_customers(const Customer& c){
    customers.push_back(c);
    total_customers++;
}

bool Database::find_customers(int id){
    for(int i=0;i<total_customers;i++){
        if((customers[i].get_id())==id){
            return true;
        }
    }
    return false;
}

Customer& Database::customer_getter(int id){
    for(int i=0;i<total_customers;i++){
        if((customers[i].get_id())==id){
            return customers[i];
        }
    }
    return customers[0];
}

class SuperMarket {
    string password;
    Stock stock;
    Customer_Cart cart;
    Office office;
    Database database;
    bool runtime;
    int restock_id;
public:
    SuperMarket(){
        Cashier temp = Cashier(1,"Rezuan");
        office.add_cashier(temp);
        password="KUET2107075";
        runtime=0;
        restock_id=1000;
    }
    void start_shopping();
    void Stock();
    void modeselect();
    void management();
    ~SuperMarket(){;}
};

void SuperMarket::management(){
    int q=0,p=0;
    string pass;
    cout<<"===========================================================================\v"<<endl;
    cout<<"       ::::PLEASE ENTER THE PASSWORD TO VERIFY YOUR IDENTITY:::"<<endl<<endl<<endl;
    cout<<"Password: "<<endl;
    cin>>pass;
    if(pass==password){
        system("cls");
        cout<<"\n\n\n\n";
        cout<<"           WELCOME TO THE SHOP, MANAGER. HOW WOULD YOU LIKE TO MANAGE THE SHOP TODAY?\v"<<endl;
        while(q!=9){
            cout<<"Choose a query::"<<endl<<endl;
            cout<<"1. Add a product"<<endl<<endl;
            cout<<"2. Remove a product"<<endl<<endl;
            cout<<"3. Show all products"<<endl<<endl;
            cout<<"4. Search a product"<<endl<<endl;
            cout<<"5. Recruit a cashier"<<endl<<endl;
            cout<<"6. Fire a cashier"<<endl<<endl;
            cout<<"7. Show all cashiers"<<endl<<endl;
            cout<<"8. Show past transactions and details of the customers"<<endl<<endl;
            cout<<"9. Exit and Finalize changes"<<endl<<endl;
            cin>>q;
            int n;
            int id, quantity;
            double price,p1,p2;
            string name, category;
            bool availability;
            switch(q){
                case 1:
                    system("cls");
                    cout<<"How do you want to stock the products?\v"<<endl;
                    cout<<"\n 1. Default Stock\n"<<endl;
                    cout<<"\n 2. Manual Stock\n"<<endl;
                    cin>>n;
                    switch(n){
                        case 1:
                            if(runtime==false){Stock();}
                            runtime=true;
                            cout<<"\nThe products have been stocked by default\v"<<endl;
                            break;
                        case 2:
                            cout<<"\vHow many products do you want to add?"<<endl<<endl;
                            cin>>n;
                            cout<<endl;
                            for(int i = 0;i<n;i++){
                                cout<<"Please enter the id of the product"<<endl<<endl;
                                cin>>id;
                                cout<<endl;
                                cout<<"Please enter the name of the product"<<endl<<endl;
                                cin>>name;
                                cout<<endl;
                                cout<<"Please enter the quantity of the added product"<<endl<<endl;
                                cin>>quantity;
                                cout<<endl;
                                cout<<"Please enter the price of the added product"<<endl<<endl;
                                cin>>price;
                                cout<<endl;
                                cout<<"Please enter the category of the added prdouct"<<endl<<endl;
                                cin>>category;
                                cout<<endl;
                                availability=(quantity>0)?true:false;
                                stock.add_product(Product(id,price,quantity,name,category,availability));
                        }
                            break;
                    }
                    break;
                case 2:
                    system("cls");
                    cout<<"\vHow many products do you want to remove?\v"<<endl;
                    cin>>n;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the product:"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        stock.remove_product(stock.prod_return(id), quantity);
                    }
                    break;
                case 3:
                    system("cls");
                    stock.show_product();
                    break;
                case 4:
                    system("cls");
                    cout<<"Choose the way you want to search the products\v"<<endl;
                    cout<<"\n 1. Search by id\n"<<endl;
                    cout<<"\n 2. Search by name\n"<<endl;
                    cout<<"\n 3. Search by category\n"<<endl;
                    cout<<"\n 4. Search by price range\n"<<endl;
                    cin>>n;
                    switch(n){
                        case 1:
                            cout<<"\nPlease enter the id of the product\n"<<endl;
                            cout<<"ID:"<<endl<<endl;
                            cin>>id;
                            cout<<endl;
                            stock.search_product(id);
                            break;
                        case 2:
                            cout<<"\nPlease enter the name of the product\n"<<endl;
                            cout<<"Name:"<<endl<<endl;
                            cin>>name;
                            cout<<endl;
                            stock.search_product(id);
                            break;
                        case 3:
                            cout<<"\nPlease enter the category of the product\n"<<endl;
                            cout<<"ID:"<<endl<<endl;
                            cin>>category;
                            cout<<endl;
                            stock.search_product(category,id=0);
                            break;
                        case 4:
                            cout<<"\nPlease enter the price range of the product\n"<<endl;
                            cout<<"Lowest Price range:"<<endl<<endl;
                            cin>>p1;
                            cout<<endl;
                            cout<<"Highest Price range:"<<endl<<endl;
                            cin>>p2;
                            cout<<endl;
                            stock.search_product(p1,p2);
                            break;
                    }
                    break;
                case 5:
                    system("cls");
                    cout<<"\vHow many employees do you want to recruit?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the employee"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        cout<<"Please enter the name of the employee"<<endl<<endl;
                        cin>>name;
                        cout<<endl;
                        office.add_cashier(Cashier(id,name));
                    }
                    break;
                case 6:
                    system("cls");
                    cout<<"\vHow many employees do you want to fire?"<<endl<<endl;
                    cin>>n;
                    cout<<endl;
                    for(int i = 0;i<n;i++){
                        cout<<"Please enter the id of the employee"<<endl<<endl;
                        cin>>id;
                        cout<<endl;
                        office.remove_cashier(id);
                    }
                    break;
                case 7:
                    system("cls");
                    office.show_cashiers();
                    break;
                case 8:
                    database.show_all();
                    break;
                case 9:
                    cout<<"\vYOUR REQUESTS HAVE BEEN SUCCESSFULLY PROCESSED!!!\v";
                    break;
            }
        }
    }
    else{
        system("cls");
        cout<<"                     YOU ARE NOT THE MANAGER!!!"<<endl;
        cout<<"                   MANAGEMENT SYSTEM IS EXITING...\v";
        return;
    }
}

void SuperMarket::Stock() {
    stock.add_product(Product(1, 130, 7, "Cake", "Food", 1));
    stock.add_product(Product(2, 80, 10, "Biscuit", "Food", 1));
    stock.add_product(Product(3, 800, 2, "Honey Nuts", "Food", 1));
    stock.add_product(Product(4, 100, 18, "Notebook", "Stationary", 1));
    stock.add_product(Product(5, 10, 40, "Pens", "Stationary", 1));
    stock.add_product(Product(6, 250, 1, "Books", "Stationary", 1));
    stock.add_product(Product(7, 400, 0, "Napa Extra", "Medical", 0));
    stock.add_product(Product(8, 60, 3, "Napa Extend", "Medical", 1));
    stock.add_product(Product(9, 50, 5, "Reset", "Medical", 1));
    stock.add_product(Product(10, 40, 13, "Paracetamol", "Medical", 1));
}

void SuperMarket::start_shopping() {
    int id = 0, q=0, p=0, pro_id, quantity,n;
    double p1,p2;
    string name, category, address, contact_num, email, gender, choice = "Yes";
    cout<<"================================================================================================\v"<<endl;
    cout << "-------------------------------- -WELCOME TO OUR SUPERSHOP!!!----------------------------------\v" << endl;
    cout <<"          I am " << (office.get_cashier(0).getname()) << ", the cashier and I will be here the whole time to assist you!\v" << endl;
    cout << "BUT BEFORE YOU CAN START BROWSING AND START SHOPPING HERE WE NEED TO REGISTER YOUR INFORMATIONS!!!\v\v" << endl;
    cin.ignore();
    fflush(stdin);
    cout<<"Please enter your id:"<<endl<<endl;
    cin>>id;
    cout<<endl;
    cart.removeall();
    if(!database.find_customers(id)){
        cin.ignore();
        fflush(stdin);
        cout << "Please enter your name:" << endl<<endl;
        getline(cin, name);
        cout<<endl;
        cout << "Please enter your address:" << endl<<endl;
        getline(cin, address);
        cout<<endl;
        cout << "Please enter your contact number:" << endl<<endl;
        getline(cin, contact_num);
        cout<<endl;
        cout << "Please enter your email address:" << endl<<endl;
        getline(cin, email);
        cout<<endl;
        cout << "Please enter your gender:" << endl<<endl;
        getline(cin, gender);
        cout<<endl;
        database.add_customers(Customer(id, name, address, contact_num, email, gender));
        gender = (gender == "Male") ? " Sir" : " Madam";
        cout << "Thank you for being with us here today " << database.customer_getter(id).get_name() <<", "<< gender <<"!\v"<< endl;
        cout << "Please let us know how can we be of your service today," << gender << ":\v" << endl<<endl;
    }
    else{
        cout<<endl;
        if(restock_id!=1000) stock.restock(stock.prod_return(restock_id));
        system("cls");
        cout<<"=================================================================================================\v"<<endl;
        gender = ((database.customer_getter(id).get_gender()=="Male")?"Sir!":"Madam!");
        cout<<"Welcome Back, "<< database.customer_getter(id).get_name()<<" "<<gender<<"\v"<<endl;
        cout << "Please let us know how can we be of your service today," << gender << ":\v" << endl<<endl;
        cout <<"=================================================================================================\v\v\v"<<endl;
    }
    while (q != 5) {
        cout << "1. Show the whole inventory of products" << endl<<endl;
        cout << "2. Show only the available products" << endl<<endl;
        cout << "3. Start Shopping from the available products" << endl<<endl;
        cout << "4. Request Restock of an unavailable product" << endl<<endl;
        cout << "5. Exit & Process your purchase" << endl<<endl;
        cin >> q;
        switch (q) {
        case 1:
            stock.show_product();
            break;
        case 2:
            stock.show_avail();
            break;
        case 3:
            system("cls");
            stock.show_avail();
            p = 0;
            while (p != 5) {
                cout << "Choose your query" << endl<<endl;
                cout << "1. Add a product to cart" << endl<<endl;
                cout << "2. Remove a product from cart" << endl<<endl;
                cout << "3. Search a product"<<endl<<endl;
                cout << "4. Show your cart" << endl<<endl;
                cout << "5. Checkout" << endl<<endl;
                cin >> p;
                switch (p) {
                case 1:
                    do {
                        cout << "\nWhich product do you want?Please enter it's id and quantity:" << endl<<endl;
                        cout << "ID: " << endl<<endl;
                        cin >> pro_id;
                        cout<<endl;
                        cout << "Quantity: " << endl<<endl;
                        cin >> quantity;
                        cout<<endl;
                        if (stock.if_avail(pro_id, quantity)) {
                            cart.add_to_cart(stock.prod_return(pro_id), quantity);
                            stock.remove_product(stock.prod_return(pro_id), quantity);
                            cout<<"The product has been successfully added to your cart\v"<<endl;
                        }
                        else {
                            cout << "This product is not currently available\v" << endl;
                        }
                        cout << "Do you want to add more products?Type Yes/yes if you want to." << endl<<endl;
                        cin >> choice;
                        cout<<"\v"<<endl;
                    } while (choice == "Yes" || choice == "yes");
                    break;
                case 2:
                    do {
                        cout << "\nWhich product do you want to remove from the cart?Please enter it's id and quantity:" << endl;
                        cout << "ID: " << endl<<endl;
                        cin >> pro_id;
                        cout<<endl;
                        cout << "Quantity: " << endl<<endl;
                        cin >> quantity;
                        cout<<endl;
                        bool av= cart.remove_from_cart(stock.prod_return(pro_id), quantity);
                        if(av)stock.update_quantity(stock.prod_return(pro_id), quantity);
                        cout<<"The product has been successfully removed from your cart\v"<<endl;
                        cout << "Do you want to remove more products?Type Yes/yes if you want to." << endl<<endl;
                        cin >> choice;
                        cout<<"\v"<<endl;
                    } while (choice == "Yes" || choice == "yes");
                    break;
                case 3:
                    system("cls");
                    cout<<"Choose the way you want to search the products\v"<<endl;
                    cout<<"\n 1. Search by id\n"<<endl;
                    cout<<"\n 2. Search by name\n"<<endl;
                    cout<<"\n 3. Search by category\n"<<endl;
                    cout<<"\n 4. Search by price range\n"<<endl;
                    cin>>n;
                    switch(n){
                        case 1:
                            cout<<"\nPlease enter the id of the product\n"<<endl;
                            cout<<"ID:"<<endl;
                            cin>>id;
                            stock.search_product(id);
                            break;
                        case 2:
                            cout<<"\nPlease enter the name of the product\n"<<endl;
                            cout<<"Name:"<<endl;
                            cin>>name;
                            stock.search_product(id);
                            break;
                        case 3:
                            cout<<"\nPlease enter the category of the product\n"<<endl;
                            cout<<"ID:"<<endl;
                            cin>>category;
                            stock.search_product(category,0);
                            break;
                        case 4:
                            cout<<"\nPlease enter the price range of the product\n"<<endl;
                            cout<<"Lowest Price range:"<<endl<<endl;
                            cin>>p1;
                            cout<<endl;
                            cout<<"Highest Price range:"<<endl<<endl;
                            cin>>p2;
                            cout<<endl;
                            stock.search_product(p1,p2);
                            break;
                    }
                    break;
                case 4:
                    cout << "You have " << cart.get_prod() << " products in your cart" << endl;
                    cart.show_cart();
                    break;
                case 5:
                    system("cls");
                    cout << "You have " << cart.get_prod() << " products in your cart" << endl;
                    cart.show_cart();
                    cout << "\vTotal price: " << cart.total_price_calc() << " Tk/-\v" << endl;
                    cout <<"\vChecking out.......\v"<<endl;
                    break;
                }
            }
            break;
        case 4:
            cout<<"\nPlease enter the id of the product which you want to be restocked:"<<endl<<endl;;
            cout<<"ID: "<<endl;
            cin>>restock_id;
            cout<<endl;
            cout << "\nYour request has been processed! Thanks for your input!" << endl<<endl;;
            break;
        case 5:
            system("cls");
            office.get_cashier(0).process_payment(cart, database.customer_getter(id));
            break;
        }
    }
}

void SuperMarket::modeselect(){
    int n=0;
    while(n!=3){
        cout<<"\v\v=====================================================================\v"<<endl;
        cout<<"-------------------------------------------------------------------"<<endl;
        cout<<"|             Welcome to the Supershop Management System          |"<<endl;
        cout<<"-------------------------------------------------------------------\v"<<endl;
        cout<<"                   ::Choose a mode to login::                    \v"<<endl;
        cout<<"1. Store Manager"<<endl;
        cout<<"2. Customer"<<endl;
        cout<<"3. Exit"<<endl;
        cin>>n;
        switch(n){
            case 1:
                management();
                break;
            case 2:
                if(runtime==false){Stock();}
                start_shopping();
                runtime=true;
                break;
            case 3:
                cout<<"===============================================================================\v"<<endl;
                cout<<"\v|------------------THANKS FOR CHOOSING OUR SERVICE, MADE BY SARWAD----------------------|\v"<<endl<<endl;
                cout<<"               THE MANAGEMENT SYSTEM IS EXITING...\v"<<endl;
                break;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    SuperMarket Shwapno;
    Shwapno.modeselect();
    return 0;
}
