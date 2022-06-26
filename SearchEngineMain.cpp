#include "menus.h"


int main()
{
	vector<website> websitevector;

	//READING KEYWORD FILE
	vector<string> row1;
	string line, word;
	string link;
	fstream file1("keywordfile.txt", ios::in);
	if (file1.is_open())
	{
		while (getline(file1, line))
		{
			row1.clear();

			stringstream str(line);

			while (getline(str, word, ',')) {
				row1.push_back(word);
			}

			link = row1[0];
			row1.erase(row1.begin());
			website currentwebsite;
			currentwebsite.setLink(link);
			currentwebsite.setKeywords(row1);
			websitevector.push_back(currentwebsite);



		}
	}
	//READING IMPRESSIONS FILE
	vector<string> row2;
	string line2, word2;
	fstream file2("impressionfile.txt", ios::in);

	if (file2.is_open())
	{
		while (getline(file2, line2))
		{
			row2.clear();

			stringstream str(line2);

			while (getline(str, word2, ',')) {
				row2.push_back(word2);
			}

			link = row2[0];
			for (int i = 0; i < websitevector.size(); i++) {
				if (websitevector[i].getLink() == link) {
					websitevector[i].setImpressions(stoi(row2[1]));
				}
			}
		}
	}

	//READING CLICKS FILE
	vector<string> row3;
	string line3, word3;
	fstream file3("clicksfile.txt", ios::in);

	if (file3.is_open())
	{
		while (getline(file3, line3))
		{
			row3.clear();

			stringstream str(line3);

			while (getline(str, word3, ',')) {
				row3.push_back(word3);
			}

			link = row3[0];
			for (int i = 0; i < websitevector.size(); i++) {
				if (websitevector[i].getLink() == link) {
					websitevector[i].setClicks(stoi(row3[1]));
				}
			}
		}
	}

	//GIVING EACH WEBSITE AN INDEX TO REPRESENT ITSELF IN THE GRAPH
	for (int i = 0; i < websitevector.size(); i++) {
		websitevector[i].setIndex(i);
	}
	Graph WebsiteGraph(websitevector.size());


	//READING WEBGRAPH FILE
	vector<string> row4;
	string line4, word4;
	fstream file4("webgraphfile.txt", ios::in);
	string startlink, endlink;
	int startindex, endindex;
	if (file4.is_open())
	{
		while (getline(file4, line4))
		{
			row4.clear();

			stringstream str(line4);

			while (getline(str, word4, ',')) {
				row4.push_back(word4);
			}

			startlink = row4[0];
			endlink = row4[1];

			for (int i = 0; i < websitevector.size(); i++) {
				if (websitevector[i].getLink() == startlink) {
					startindex = websitevector[i].getIndex();
				}
			}
			for (int i = 0; i < websitevector.size(); i++) {
				if (websitevector[i].getLink() == endlink) {
					endindex = websitevector[i].getIndex();
				}
			}
		
			WebsiteGraph.addEdge(startindex, endindex);
		}
	}

	
	string searchquery;
	vector<website> finalsearchvector;
	bool programexit = false;

	welcomePage();
   
	int initialuserchoice = enterUserChoice();
	system("cls");
   
    if (initialuserchoice == 2) {

        cout << "Program exited" << endl;
    }
    else {

	searchquerymenu: searchquery = searchQuery();
		
    system("cls");

		//RUN WHILE PROGRAM HAS NOT BEEN EXITED
        while (programexit == false) {
			//NEW SEARCH
            if (initialuserchoice == 1) {
              
				finalsearchvector = searchEngine(websitevector,WebsiteGraph,searchquery); 
				int userchoice= enterUserChoice();
			  //SEARCH MENU
               if (userchoice == 1) {
				   //WEBSITE VIEW
                   cout << "Select which website you want to view:" << endl;
                   cin >> userchoice; 

                   system("cls");

                   viewPage(finalsearchvector[userchoice-1],websitevector); //CHOSEN WEBSITE PASSED TO VIEW PAGE
                   userchoice = enterUserChoice();   

                   system("cls");
               }
			   //NEW SEARCH
               if (userchoice == 2) {
                   system("cls");
				   //RETURN TO SEARCH QUERY MENU
                   goto searchquerymenu;
               }
			   //PROGRAM EXIT
                if (userchoice == 3) {
                    programexit = true;
                    cout << "Program Exited";
                }    
            }
        }
    }
    


}


