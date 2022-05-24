#include "../include/classifier.h"

classifier::classifier(){
    datasets = {};
}

//Also known as train(), take the set of training instances and get them into the system

void classifier::parse(){
    int setBuffer;
    
    std::cout << "Select a dataset to use:\n[1] - Baby Set (5 Instances, 3 Features\n[2] - Small Set (100 Instances, 10 Features)\n[3] - Large Set (1000 Instances, 40 Features)\n";
    std::cout << "[4] - Personal Small Dataset [155] (100 Instances, 10 Features)\n[5] - Personal Large Dataset [155] (1000 Instances, 40 Features)\nPlease enter your selection: ";
    std::cin >> setBuffer; 
    
    std::string fileName;
    int dataSize;
    int classType;
    std::vector<float> features = {};
    datasets.clear();
    
    switch(setBuffer){
        case 1:
            fileName = "datasets/baby_dataset.txt";
            dataSize = 3;
            break;
        case 2:
            fileName = "datasets/small_dataset.txt";
            dataSize = 10;
            break;
        case 3:
            fileName = "datasets/large_dataset.txt";
            dataSize = 40;
            break;
        case 4:
            fileName = "datasets/personal_small_dataset.txt";
            dataSize = 10;
            break;
        case 5:
            fileName = "datasets/personal_large_dataset.txt";
            dataSize = 40;
            break;
        default:
            break;
    }
    
    std::ifstream infile;
    infile.open(fileName);

    float buffer;

    auto start = high_resolution_clock::now();

    while(infile >> buffer){
        classType = buffer;
        for(int i = 0; i < dataSize; i++){
            infile >> buffer;
            features.push_back(buffer);
        }
        dataset* temp = new dataset(classType, features);
        datasets.push_back(temp);
        features.clear();
    }

    auto stop = high_resolution_clock::now();

    infile.close();

    auto duration = duration_cast<microseconds>(stop-start);

    std::cout << "Program took "  << duration.count() << " ms to parse the data\n";
}

int classifier::test(int instance_index, std::vector<int>subsets){
    dataset* testInstance = datasets[instance_index];
    dataset* currentNearest = new dataset();

    double closest = std::numeric_limits<double>::max();
    for(int i = 0; i < datasets.size(); i++){
        if(i == instance_index){
            continue;
        }
        double eucl = getDistance(datasets[instance_index], datasets[i], subsets);
        if(eucl < closest){
            closest = eucl;
            currentNearest = datasets[i];
        }
    }

    return currentNearest->getInstance();
}

void classifier::normalizeData(){
    double mean;
    double total;
    double sd;
    
    auto start = high_resolution_clock::now();

    for(int i = 0; i < datasets[0]->getFeatureCount(); i++){
        mean = total = sd = 0;
        for(int j = 0; j < datasets.size(); j++){
            total += datasets[j]->getFeatureValue(i);
        }

        mean = total / datasets.size();

        for(int k = 0; k < datasets.size(); k++){
            sd += pow(datasets[k]->getFeatureValue(i) - mean, 2);
        }

        sd = sd / (datasets.size() - 1);

        sd = sqrt(sd);

        for(int l = 0; l < datasets.size(); l++){
            float temp = (datasets[l]->getFeatureValue(i) - mean) / sd;
            datasets[l]->setFeatureValue(i, temp);
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Program took " << duration.count() << " ms to normalize the data\n";
}

double classifier::getDistance(dataset* a, dataset* b, std::vector<int> features){
    std::vector<double> under = {};
    // Compute Stuff Underneath the Square Root

    for(int i = 0; i < features.size(); i++){
        double temp = b->getFeatureValue(features[i]) - a->getFeatureValue(features[i]);
        temp = pow(temp, 2);
        under.push_back(temp);
    }

    // Compute Sum of stuff under the square root

    double under_sum = 0;

    for(int i = 0; i < under.size(); i++){
        under_sum += under[i];
    }

    return std::sqrt(under_sum);
}

double classifier::getDefaultRate(){
    double instance_one = 0;
    double instance_two = 0;

    for(unsigned i = 0; i < datasets.size(); i++){
        if(datasets.at(i)->getInstance() == 1){
            instance_one++;
        }
        else{
            instance_two++;
        }
    }

    if(instance_one > instance_two){
        return instance_one / datasets.size();
    }
    else{
        return instance_two / datasets.size();
    }
}

int classifier::getDataSize(){
    return datasets.size();
}

int classifier::getFeatureSize(){
    return datasets[0]->getFeatureCount();
}

int classifier::getClassLabel(int i){
    return datasets[i]->getInstance();
}

void classifier::print(){
    for(int i = 0; i < datasets.size(); i++){
        datasets[i]->print();
        std::cout << std::endl;
    }
}

void classifier::subsetInput(std::vector<int> &f){
    std::cout << "Enter the sub-sets you would like to use (1 - " << getFeatureSize() << "): ";
    int buffer;

    do{
        std::cin >> buffer;
        f.push_back(buffer);
    }
    while(std::cin.peek() == ' ');

    for(int i = 0; i < f.size(); i++){
        f[i] = f[i] - 1;
    }
}