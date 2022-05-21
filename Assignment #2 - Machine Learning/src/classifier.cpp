#include "../include/classifier.h"

classifier::classifier(){
    datasets = {};
}

//Also known as train(), take the set of training instances and get them into the system

void classifier::parse(){
    int setBuffer;
    
    std::cout << "Select a dataset to use:\n[1] - Baby Set (5 Instances, 3 Features\n[2] - Small Set (100 Instances, 10 Features)\n[3] - Large Set (1000 Instances, 40 Features)\nPlease enter your selection: ";
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

void classifier::print(){
    for(int i = 0; i < datasets.size(); i++){
        datasets[i]->print();
        std::cout << std::endl;
    }
}