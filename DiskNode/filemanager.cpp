#include "filemanager.h"

FileManager::FileManager()
{

}

Table FileManager::loadTableFromDisk(std::string filename)
{
    Table result;
    result.setName(filename);
    std::ifstream txtFileStream;
    filename.append(".table");
    txtFileStream.open(filename);
    std::string tempString="999";
    int cols,rows;
    if(txtFileStream.is_open()){
        getline(txtFileStream,tempString,'\n');

        std::vector<std::string> tableAttributes;
        for (int i = 0; i < 2; i++) {
            std::string parameter =tempString.substr(0,tempString.find_first_of("|"));
            tempString.erase(0, parameter.size()+1);                            //std::cout << enemyFile;
            tableAttributes.push_back(parameter);
        }
        cols = std::stoi(tableAttributes[0]);
        rows = std::stoi(tableAttributes[1]);
        std::cout<<"cols: "<<cols<<"rows:  "<<rows<<"\n";

        //std::vector<std::string> columNames;
        getline(txtFileStream,tempString,'\n');
        for (int col = 0; col < cols; ++col) {
            std::string parameter = tempString.substr(0,tempString.find_first_of("|"));
            tempString.erase(0, parameter.size()+1);                            //std::cout << enemyFile;
            //tableAttributes.push_back(parameter);
            result.insertColumn(parameter);
        }

        getline(txtFileStream,tempString,'\n');
        for (int col = 0; col < cols; ++col) {
            std::string parameter = tempString.substr(0,tempString.find_first_of("|"));
            tempString.erase(0, parameter.size()+1);                            //std::cout << enemyFile;
            //tableAttributes.push_back(parameter);
            result.setColumnType(col, std::stoi(parameter));
        }
        for (int row = 0; row < rows; ++row) {
            getline(txtFileStream,tempString,'\n');
            std::vector<std::string> contents;
            for (int i = 0; i < cols; i++) {
                std::string parameter = tempString.substr(0,tempString.find_first_of("|"));
                tempString.erase(0, parameter.size()+1);                            //std::cout << enemyFile;
                contents.push_back(parameter);
                std::cout <<"param"<<parameter<<"\n";
            }
            std::cout <<"result insert: " <<result.insertRow(contents)<<std::endl;
        }
    }
    std::cout<<result.toString()<<std::endl;
    txtFileStream.close();
    return result;
}

bool FileManager::saveTableToDisk(Table table)
{
    std::ofstream txtFileStream;
    std::string  filename= table.getName();
    filename.append(".table");
    remove( filename.c_str() );
    txtFileStream.open(filename);
    //txtFileStream.
    std::string resultString= "";
    if(txtFileStream.is_open()){
        resultString.append(std::to_string(table.getTotalColumns()) + "|");
        resultString.append(std::to_string(table.getTotalRows()) + "|");
        resultString.append("\n");

        for(const ColumnProperties &property : table.getColumnProperties()){
            resultString.append(property.getName()+"|");
        }
        resultString.append("\n");


        for(const ColumnProperties &property : table.getColumnProperties()){
            resultString.append(std::to_string(property.getType())+"|");
        }
        resultString.append("\n");

        for(const Row &row : table.getRows()){
            for(const std::string &content : row.getContents()){
            resultString.append(content+"|");
            }
            resultString.append("\n");
        }
    txtFileStream<<resultString;


    }
    /*
     *ofstream txtFileStream;
    txtFileStream.open(txtFile);
     int array[size];
     fseek(binFile, sizeof(int)*0 ,SEEK_SET);
     for (int i = 0; i < size; ++i) {
         //fseek(binFile, sizeof(int)*i ,SEEK_SET);
         fread( array, sizeof(int), 1, binFile);
         txtFileStream<<to_string(array[0])<<" ,";
     }
*/
}

bool FileManager::existsOnDisk(std::string name)
{

}

std::vector<std::string> FileManager::tablesOnDisk()
{

}
