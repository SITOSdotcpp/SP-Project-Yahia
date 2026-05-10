#include <iostream>
using namespace std;
#define size 4
struct product
{
    int serialNum, quantity, totalSales, price;
};
void displayy(product products[], int size_of_product);
void discount();
void highestsales();
void lessquantity();
void inputproduct(product products[], int size_of_product)
{
    cout << "enter value of four products: \n";
    for (int i = 0; i < size_of_product; i++)
    {
        cout << "product #" << i + 1 << '\n';
        cout << "serial umber: ";
        cin >> products[i].serialNum;
        cout << "quantity: ";
        cin >> products[i].quantity;
        cout << "sales: ";
        cin >> products[i].totalSales;
        cout << "price: ";
        cin >> products[i].price;
        cout << products[i].price;
    }
}
// void menu(){
//     char choice;
//     do{
//         cout<<"Please enter a number:\n";
//         cout<<"Press 1 to get products that have less quantity than a certain value\n";
//         cout<<"Press 2 to Get Product with the highest sales \n";
//         cout<<"Press 3 to Apply 50% discount for products that have quantity less than 6\n";
//         cout<<"Press 4 to Display all the products \n";
//         int n;
//         cin>>n;
//         if(n == 1){
//             lessquantity();
//         }
//         else if(n == 2){
//             highestsales();
//         }
//         else if(n == 3){
//             discount();
//         }
//         else if(n == 4){
//             displayy();
//         }
//         else {
//             cout<<"invalid number \n please re-enter number \n";
//             menu();
//         }
//         cout<<"Do you want to Apply Another function, Press 'Y' or 'y' for yes, any other key to stop :";
//         cin>>choice;
//     } while (choice == 'Y' || choice == 'y');
// }
// void  lessquantity(){
//     int quant;
//     cout<<"Please enter the quantity:";
//     cin>>quant;
//     for(int i=0;i<size_of_product;i++){
//         if( quant > products[i].quantity){
//             cout<<"product "<<products[i].serialNum<<'\n';
//         }
//     }
// }
// void highestsales(){
//     int max_index=0, max= products[0].totalSales;
//     for( int i=0 ; i<size_of_product ; i++){
//         if(products[i].totalSales > max ){
//             max_index=i;
//         }
//     }
//     cout<<"product "<<max_index<<'\n';
// }
// void discount(){
//     for(int i=0 ; i<size_of_product ; i++){
//         if(products[i].quantity < 6){
//             products[i].price/=2;
//         }
//     }
//     cout<<"discount applied \n";
// }
// void displayy(){
//     for(int i = 0 ; i < size_of_product ; i++){
//         cout<<"product #"<<i+1<<'\n';
//         cout<<"serial umber: ";
//         cout<<products[i].serialNum<<'\n';
//         cout<<"quantity: ";
//         cout<<products[i].quantity<<'\n';
//         cout<<"sales: ";
//         cout<<products[i].totalSales<<'\n';
//         cout<<"price: ";
//         cout<<products[i].price<<'\n';
// }
// }
int main()
{
    int size_of_product;
    cout << "Enter the number of products: ";
    cin >> size_of_product;
    product products[size_of_product];
    inputproduct(products, size_of_product);
    return 0;
}