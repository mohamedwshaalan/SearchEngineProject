#include "menus.h"

void welcomePage() {

    cout << "Welcome!" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. New Search" << endl;
    cout << "2. Exit" << endl;
}

void viewPage(website viewingwebsite,vector<website> websitevector) {

    for (int i = 0; i < websitevector.size(); i++) {
            if (websitevector[i].getLink() == viewingwebsite.getLink()) {
                websitevector[i].addClick();
            }
        }
    ofstream outputtwo;
    outputtwo.open("clicksfile.txt");
    for (int i = 0; i < websitevector.size(); i++)
        outputtwo << websitevector[i].getLink() << "," << websitevector[i].getClicks() << endl;
    
    cout << "You are now viewing " << viewingwebsite.getLink() << endl;
    cout << "Would you like to" << endl;
    cout << "1.Back to search results" << endl;
    cout << "2.New Search" << endl;
    cout << "3.Exit" << endl;
}

int enterUserChoice() {
    cout << "Type in your choice:";
    int userchoice;
    cin >> userchoice;
    return userchoice;
}

string searchQuery() {
    
    cout << "Enter Search query: " << endl;
    string searchquery;
     cin.ignore();
    getline(cin, searchquery);
    return searchquery;
}

vector<website> sortByscore(vector<website> websitevector) {

    //BUBBLE SORT BY SCORE VALUE
    for (int i = 0; i < websitevector.size()-1; i++){
        if (websitevector[i].getScore() < websitevector[i+1].getScore()) {
            website temp = websitevector[i];
            websitevector[i]= websitevector[i+1];
            websitevector[i + 1] = temp;
        }
    }
    return websitevector;
    
}

vector<website> getSortedWebsiteVector(vector<website> websitevector, Graph websitegraph){

    vector<website> finalresultvector;

    vector<int> finalpagerankvector;
    vector<vector<double>> pageranktable; //PAGE RANK TABLE 
    vector<double> initialpagerankrow(websitevector.size(), 1 / double(websitevector.size())); //GET INITIAL PAGE RANK ROW
    pageranktable.push_back(initialpagerankrow); 
    double currentrank = 0;
    vector<double> currentrow;
    //PAGE RANK TABLE = websitevector.size()*websitevector.size()
    for (int i = 1; i < websitevector.size(); i++) { // STARTING FROM 1 BECAUSE FIRST ROW DONE
        for (int j = 0; j < websitevector.size(); j++) {
            vector<int> incomingwebsites = websitegraph.getIncomingwebsites(j);
            //SUMMATION OVER AMOUNT OF INCOMING WEBSITES
            for (int k = 0; k < incomingwebsites.size(); k++) {
                currentrank = currentrank + (pageranktable[i - 1][incomingwebsites[k]] / websitegraph.getOutgoingwebsitenumber(incomingwebsites[k]));
            }
            //ADD CURRENT RANK IN ROW OF PAGE RANK TABLE
            currentrow.push_back(currentrank);
            //RESET CURRENT RANK
            currentrank = 0;
        }
        //PUSH CURRENT ROW IN PAGE RANK TABLE
        pageranktable.push_back(currentrow);
        //RESET CURRENT ROW
        currentrow.clear();
    }
    //GET FINAL PAGE RANK FROM FINAL PAGE RANK TABLE ROW AND PUSH INTO WEBSITEVECTOR
    for (int i = 0; i < websitevector.size(); i++) {
        websitevector[i].setPagerank(pageranktable[websitevector.size() - 1][i]);
   
    }
    //CALCULATE CTR AND PUSH INTO WEBSITEVECTOR
    for (int i = 0; i < websitevector.size(); i++) {
        websitevector[i].setCTR();

    }

   //CALCULATE SCORE AND PUSH INTO WEBSITEVECTOR
    for (int i = 0; i < websitevector.size(); i++) {
        websitevector[i].setScore();
       
    }

    //SORT WEBSITE VECTOR BY SCORE DESCENDINGLY
    vector<website> sortedwebsitevector = sortByscore(websitevector);
   
    return sortedwebsitevector;
    
}

string getSearchType(string searchquery) {

    int n = searchquery.size();
    
    if (searchquery[0] == '"' || searchquery[n - 1] == '"') {
        return "QUOTES";
    }
    stringstream ss(searchquery);
    string word;
    char space = ' ';
    
    vector<string> searchqueryvector;
    while (getline(ss, word, space)) {
        searchqueryvector.push_back(word);
    }

    for (int i = 0; i < searchqueryvector.size(); i++) {
        if (searchqueryvector[i] == "AND") {
            return "AND";
        }
        if (searchqueryvector[i] == "OR") {
            return "OR";
        }
    }
   

    
    return "NORMAL";
}

vector<string> getSearchedWords(string searchquery) {
    //"NORMAL" CASE NOT INCLUDED BECAUSE IT HAS NO ADDITIONAL INFO IN ITS STRING 
    string searchtype = getSearchType(searchquery);
    stringstream ss(searchquery);
    string word;
    char space = ' ';
    
    vector<string> searchedwordsvector;
    while(getline(ss, word,space)) {
        searchedwordsvector.push_back(word);
    }
   
    if (searchtype == "QUOTES" ) {
        //REMOVE '"' (QUOTES) FROM STRING
        string fullword = searchquery.substr(1, searchquery.length() - 2);
        searchedwordsvector.clear();
        //ADDS FULL STRING WITHOUT QUOTES AS A SEARCH WORD
        searchedwordsvector.push_back(fullword);
        return searchedwordsvector;
    }
    else{
        //REMOVING "AND" and "OR" FROM SEARCH QUERY
        for (int i = 0; i< searchedwordsvector.size(); i++) {
            if (searchedwordsvector[i] == "OR") {
                //REMOVES "OR" FROM VECTOR
                searchedwordsvector.erase(searchedwordsvector.begin() + i);
            }
            if (searchedwordsvector[i] == "AND") {
                //REMOVES "AND" FROM VECTOR
                searchedwordsvector.erase(searchedwordsvector.begin() + i);
            }
        }
        return searchedwordsvector;
    }
    
        
} 

vector<website> getRelevantwebsites(vector<string> searchedwordsvector, vector<website> websitevector, string searchType) {

    vector<website> finalwebsitevector;
    vector<string> currentwebsitekeywords;
    int searchwordsvectorsize = searchedwordsvector.size();
    //int i = 0;
    int truenumber=0;
    int falsenumber = searchwordsvectorsize;
    int websitevectorsize = websitevector.size();
    
    for(int i=0; i< websitevectorsize;i++) {
        truenumber = 0;
        falsenumber = searchwordsvectorsize;
        currentwebsitekeywords = websitevector[i].getKeywords();

        for (int j = 0; j < searchedwordsvector.size(); j++) {
            for (int k = 0; k < currentwebsitekeywords.size(); k++) {
                if (searchedwordsvector[j] == currentwebsitekeywords[k]) {
                    falsenumber--;
                    truenumber++;
                    break;
                }

            }
        }
        if (searchType == "OR" || searchType == "NORMAL") {
            
            if (truenumber != 0) { //IF ATLEAST ONE IS FOUND THEN PUSH
                finalwebsitevector.push_back(websitevector[i]);
            }
        }
        if (searchType == "QUOTES" || searchType == "AND") {

            if (falsenumber == 0) { //ONLY PUSH IF IT IS FOUND IN ALL
                finalwebsitevector.push_back(websitevector[i]);
            }
        }
    }
    return finalwebsitevector;

}

vector<website> searchEngine(vector<website> websitevector, Graph websitegraph,string searchquery) {
    
    //RETURN VECTOR WITH WEBSITES SORTED DESCENDINGLY BY SCORE
    vector<website> sortedwebsitevector= getSortedWebsiteVector(websitevector, websitegraph);
    //RETURN VECTOR WITH SEARCHED WORDS DEPENDING ON SEARCH TYPE
    vector<string> searchedwordsvector = getSearchedWords(searchquery);
    //RETURN VECTOR WITH FINAL WEBSITES ACCORDING TO SEARCH QUERY
    vector<website> relevantwebsites = getRelevantwebsites(searchedwordsvector,websitevector,getSearchType(searchquery));

     cout << "Search Results: " << endl;
     for (int i = 0; i < relevantwebsites.size(); i++) {
         cout << (i+1) << "."<< relevantwebsites[i].getLink() << endl;
     }
     cout << endl;
     for (int i = 0; i < websitevector.size(); i++) {
         for (int j = 0; j < relevantwebsites.size(); j++) {
             if (websitevector[i].getLink() == relevantwebsites[j].getLink()) {

                 websitevector[i].addImpression();    

             }
         }
     }

 ofstream outputone;
 outputone.open("impressionfile.txt");
 for (int i = 0; i < websitevector.size(); i++)
     outputone << websitevector[i].getLink() << "," << websitevector[i].getImpressions() << endl;


 cout << "1.Choose a webpage to open" << endl;
 cout << "2.New Search" << endl;
 cout << "3.Exit" << endl;

 return relevantwebsites;
    
    

}