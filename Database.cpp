#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Car {
private:
    int index;
    string brand;
    string model;
    int year;
    string numberplate;
public:
    void outputbyclass(Car *car);
    int get_car();
    int refresh(int id);
    int output_compact();
    void update();
    int insert();
    int deletecar(int id);
    int erase();
};

void Car::update() {
    int n;
    output_compact();
    cout << "Enter index of cr ";
    cin >> n;

}
int Car::get_car() {
    FILE* file;
    Car  car;
    int index;

    if ((fopen_s(&file, "CARS", "r+b")) == NULL) {
        perror("Error opening");
        return 1;
    }
    cout << "Enter the index of client: " << endl;
    cin>>index;

    while (fread(&car, sizeof(Car), 1, file) == 1) {
        if (car.index == index)
            break;
    }
    cout<<"client   \n"<< index<<endl;

    if (car.index != index)
        perror("Client, hasn't been found.Please enter correctly");
    else {
        cout<<"  id - %d\n    name - %s\n   mobile %d\n"<<car.index<<car.brand<<car.model<<car.year<<car.numberplate;
        cout<<"------------------------\n"<<index;
    }

    fclose(file);
    return 0;
}

int Car::refresh(int id) {
    FILE* fp;
    Car car;
    int changer;
    bool found = false;

    if ((fopen_s(&fp, "CARS", "r+b")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&car, sizeof(Car), 1, fp) == 1) {
        if (car.index == id) {
            found = false;
            break;
        }
    }

    if (!found) {
        perror("Client with this id not found");
        return 0;
    }
    outputbyclass(&car);
    cout << endl;
    cout << "Enter the number to change  ";
    cin >> changer;

    switch (changer) {
        case 1:
            cout<<"enter the id: \n";
            cin>>car.index;
            break;
        case 2:
            cout << "enter the brand: \n";
            cin >> car.brand;
            break;
        case 3:
            cout << "enter the model: \n";
            cin >> car.model;
            break;
        case 4:
            cout << "enter the year: \n";
            cin >> car.year;
            break;
        case 5:
            cout << "enter the bumberplate: \n";
            cin >> car.numberplate;
            break;
        default:
            perror("Number not found");
    }

    fseek(fp, sizeof(Car), SEEK_CUR);
    fwrite(&car, sizeof(Car ), 1, fp);

    fclose(fp);
}
void Car::outputbyclass(Car *car) {
    cout << "[" << car->index << "]" << endl;
    cout << "brand: " << car->brand << endl;
    cout << "model: " << car->model << endl;
    cout << "year: " << car->year << endl;
    cout << "numberplate: " << car->numberplate << endl;


}
int Car::output_compact() {
    FILE* fp;
    Car car;
    int changer=0;
   

    if ((fopen_s(&fp,"CARS", "r+b")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    cout<<"===============Cars================\n";
   cout<<"|   id, name, mobile   |\n";
    //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    while (fread(&car, sizeof(Car), 1, fp) == 1) {
        
        cout<<car.index<<car.brand<<car.model<<car.year<<car.numberplate<<endl;
    }
    printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");


    fclose(fp);
    return 0;
}

int Car:: insert() {
    FILE* file;
    Car car;
    int id;

    if ((fopen_s(&file, "CARS", "r+b") == NULL)) {
        perror("Error opening file");
        return 1;
    }
    cout<<"id of client: ";
    cin >> id;

   

    car.index = id;
    cout<< "Enter a brand of car ";
    cin>>car.brand;
    cout << endl;

    cout << "Enter a model of car  ";
    cin >> car.model;
    cout << endl;

    cout << "Enter a year of car  ";
    cin >> car.year;
    cout << endl;

    cout << "Enter a numberplate of car  ";
    cin >> car.numberplate;
    cout << endl;

    fwrite(&car, sizeof(Car), 1, file);
    fclose(file);
    return 0;
}

int Car:: deletecar(int index) {
    FILE* file;
    FILE* tmpfile;
    bool found=false;
    Car car;

    if ((fopen_s(&file, "CARS", "r+b") == NULL)) {
        perror("Error opening file");
        return 1;
    }
    if ((fopen_s(&tmpfile, "CARSTMP", "r+b")) == NULL) {
        perror("Error occured while opening file");
        return 1;
    }

    while (fread(&car, sizeof(Car), 1, file) == 1) {
        if (car.index != index)
            fwrite(&car, sizeof(Car), 1, tmpfile);
        else
            found = true;
    }
    fclose(file);
    fclose(tmpfile);

    if (found) {
        
        remove("CUSTOMERS");
        return rename("TMP_CUSTOMERS", "CUSTOMERS");
    }
    else {
        remove("CUSTOMERS");
        perror("Customer wasnt found");
    }
}

int Car::erase() {
    int n;
    output_compact();
    cout << "Enter id of car ";
    cin >> n;
    return deletecar(n);
}




int main()
{
    
}
