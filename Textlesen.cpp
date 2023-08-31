#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp> 
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/find.hpp>
#include  <algorithm>

using namespace boost::filesystem;

using namespace std;
using boost::is_any_of;

using namespace boost;


 // structure to contain player info.
struct player {
	string playername;
	string team;
	bool IsHeOnCourt;
	int OfReb;
	int DefReb;
	int PTS;
	int _2PM;
	int _3PM;
	int FTA;
	int FTM;
	int _2PA;
	int _3PA;
	int To;
	int Ast;
	int Blk;
	int PF;
	int OF;
	int St;
};


int main() {


	size_t found;
	bool IsHeOnCourt = false;
	bool cntFTM = false;
	bool Sub_in = false;
	bool Sub_out = false;
	int cnt = 0;
	int cnt2 = 0;
	int offset = -2;
	int quarter = 0;
	string  Player_List_Home_Team;   // List  of home team players in current lineup
	string  Player_List_Away_Team;   // List  of away team players in current lineup
	string time_temp = "";
	string Saison = "NULL";
	string filename;
	string Game_Time;
	string teams[2];
	string team;
	string temp;
	string temp2;
	string split;
	string date = "NULL";



	string str;
	string::size_type pos;   
	string::size_type pos_2;
	vector<string> strVec;   // vector of type string
	vector<player> StructObj;  // vector of type structure (player)


	ofstream outfile("Output/result.txt");

	outfile << setprecision(4);



	outfile << "Date" << ",";
	outfile << "Home_Team" << ",";
	outfile << "Away_Team" << ",";
	outfile << "Quarter" << ",";
	outfile << "Player" << ",";
	outfile << "Team" << ",";
	outfile << "PTS" << ",";
	outfile << "ORB" << ",";
	outfile << "DRB" << ",";
	outfile << "Two_PM" << ",";
	outfile << "Two_PA" << ",";
	outfile << "Three_PM" << ",";
	outfile << "Three_PA" << ",";
	outfile << "FTM" << ",";
	outfile << "FTA" << ",";
	outfile << "TOV" << ",";
	outfile << "AST" << ",";
	outfile << "BLK" << ",";
	outfile << "ST" << ",";
	outfile << "PF" << ",";
	outfile << "OF" << ",";
	outfile << "Sub_in" << ",";
	outfile << "Sub_out" << ",";
	outfile << "Game_Time" << ",";
	outfile << "Player_List_Home_Team" << ",";
	outfile << "Player_List_Away_Team" << ",";
	outfile << "Saison" << ",";
	outfile << "Spieltyp";
	outfile << endl;


	path p("C:/Users/mgoul/source/repos/Project_Basketball/Project_Basketball/Input");
	for (auto i = directory_iterator(p); i != directory_iterator(); i++)   // loop over all files in directory
	{

		filename = "Input/" + i->path().filename().string();

		ifstream infile(filename.c_str());


		// Start Date Berechnung
		str = i->path().filename().string();

		size_t  pos_date = 0;

		pos_date = str.find("_", pos_date);

		iterator_range<string::iterator> r = find_nth(str, "_", 2);

		int index = std::distance(str.begin(), r.begin());

		string substrin = str.substr(pos_date + 1, index + 1);

		string day = substrin.substr(0, 2);
		string month = substrin.substr(3, 2);
		string year = substrin.substr(6, 4);

		date = year + "-" + month + "-" + day;
		// End Date Berechnung



		while (getline(infile, str))     // loop over all lines in file i ( Str contains the currect line string )
		{



			cnt++;
			boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);    
	      // StrVec now contains a vector of strings, where each string is one word in the current line


			 // Start Lineup Berechnung
			pos = str.find("FIRST QUARTER");  // Get the position of the desired word in string str
			if (pos != string::npos)   // Check if the desired word exists in string str
			{
				offset = 1;
				quarter = 1;
			}



			if (offset == 1 || offset == cnt - 1)
			{
				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));      // Trim the front blank space in the line

			}


			boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);
              // StrVec now contains a vector of strings, where each string is one word in the current line


           // Lineup of home team
			if ((offset == 1 && (strVec.at(0)).size() == 3 && quarter == 1 ))
			{

				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));


				teams[0] = strVec.at(0);

           
		     //Loop over all strings in vector strVec using an iterator - Loop over all words in current line
				for (vector<string>::iterator iter = strVec.begin(); iter != strVec.end(); iter++)  
				{

					split = (*iter);


			    // If word is a playername
                    if  (split.size() >= 4)
					{
						
						while (split.find_first_not_of("~_=-|0123456789"))
						{
							found = split.find_first_of("~_=-|0123456789");
							split.erase(found, 1);          // Trim all false characters in front of player name

						}



							if (split.find(".") != string::npos)   
							{

								temp = split.substr(0, split.size() - 2);
								temp = temp + " " + split.substr(split.size() - 2);
							}
							else
								temp = split + " " + (*(iter + 1));


							pos = temp.find("_");
							if (pos != string::npos)
								temp.pop_back();    // erase character '_' at the back of the player name



							//Push back new player element in the structure vector
							StructObj.push_back(player());
							StructObj.back().playername = temp;
							StructObj.back().team = teams[0];
							StructObj.back().IsHeOnCourt = true;

				   }

				}
				offset = cnt;



			}
          
           // End Lineup of home team


         
           // Lineup of away team
			if ((cnt == offset + 1 && (strVec.at(0)).size() == 3 && quarter == 1 ))
			{

				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));


				teams[1] = strVec.at(0);



				for (vector<string>::iterator iter = strVec.begin(); iter != strVec.end(); iter++)
				{

					split = (*iter);


                         
			    // If word is a playername
                    if  (split.size() >= 4)
					{
						while (split.find_first_not_of("~_-=|0123456789"))
						{
							found = split.find_first_of("~_-=|0123456789");
							split.erase(found, 1);

						}

                  
							if (split.find(".") != string::npos)
							{

								temp = split.substr(0, split.size() - 2);
								temp = temp + " " + split.substr(split.size() - 2);
							}
							else
								temp = split + " " + (*(iter + 1));

	
							pos = temp.find("_");

							if (pos != string::npos)
								temp.pop_back();



							//Push back new player element in the structure vector
							StructObj.push_back(player());
							StructObj.back().playername = temp;
							StructObj.back().team = teams[1];
							StructObj.back().IsHeOnCourt = true;

					 }
			
				}


				std::cout << teams[0] << "\t";
				std::cout << teams[1] << "\t";
				std::cout << quarter << endl;



				offset = -2;


				Player_List_Home_Team = "";
				Player_List_Away_Team = "";


       
		     //Loop over the lements of  vector StructObj of type structure using an iterator -  Loop over all players in lineup
				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)   
				{



					if ((*it).IsHeOnCourt) {
						if ((*it).team == teams[0])
							Player_List_Home_Team = Player_List_Home_Team + (*it).playername + ";";
						else if ((*it).team == teams[1])
							Player_List_Away_Team = Player_List_Away_Team + (*it).playername + ";";

					}

				}

			}
       
			// End first Quarter Lineup Berechnung



			 // Second-Third and fourth Quarter Lineup Berechnung

			pos = str.find("SECOND QUARTER");

			if (pos != string::npos)
			{
				offset = 1;
				quarter = 2;
				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					(*it).IsHeOnCourt = false;

			}


			pos = str.find("THIRD QUARTER");
			if (pos != string::npos)
			{
				offset = 1;
				quarter = 3;
				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					(*it).IsHeOnCourt = false;

			}


			pos = str.find("FOURTH QUARTER");

			if (pos != string::npos)
			{
				offset = 1;
				quarter = 4;
				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					(*it).IsHeOnCourt = false;

			}


			pos = str.find("FIRST OVERTIME");

			if (pos != string::npos)
			{
				offset = 1;
				quarter = 5;
				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					(*it).IsHeOnCourt = false;
			}


			pos = str.find("SECOND OVERTIME");

			if (pos != string::npos)
			{
				offset = 1;
				quarter = 6;
				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					(*it).IsHeOnCourt = false;

			}



			if (offset == 1 || offset == cnt - 1)
			{
				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));

			}


			boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);


       
           // Lineup of home team
			if ((offset == 1 && strVec.at(0) == teams[0] && quarter > 1))
			{

				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));



				for (vector<string>::iterator iter = strVec.begin(); iter != strVec.end(); iter++)
				{

					split = (*iter);

			
                     
			    // If word is a playername
                    if  (split.size() >= 4)
					{
						while (split.find_first_not_of("~_=-|0123456789"))
						{
							found = split.find_first_of("~_=-|0123456789");
							split.erase(found, 1);

						}



							if (split.find(".") != string::npos)
							{

								temp = split.substr(0, split.size() - 2);
								temp = temp + " " + split.substr(split.size() - 2);
							}
							else
								temp = split + " " + (*(iter + 1));

							
							pos = temp.find("_");

							if (pos != string::npos)
								temp.pop_back();



							for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
							{
								if ((*it).playername == temp)
								{
									(*it).IsHeOnCourt = true;
									cnt2 = 1;
								}
							}

							if (cnt2 == 0)
							{
								StructObj.push_back(player());
								StructObj.back().playername = temp;
								StructObj.back().team = strVec.at(0);
								StructObj.back().IsHeOnCourt = true;


							}

					}
					cnt2 = 0;
                  
				    
				}

				offset = cnt;


			}
                  // End Lineup of home team


           // Lineup of away team
			if ((cnt == offset + 1 && strVec.at(0) == teams[1] && quarter > 1))
			{

				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));



				for (vector<string>::iterator iter = strVec.begin(); iter != strVec.end(); iter++)
				{
		
						split = (*iter);


			        // If word is a playername
                   if  (split.size() >= 4)
					  {
						
						while (split.find_first_not_of("~_=-|0123456789"))
						{
							found = split.find_first_of("~_=-|0123456789");
							split.erase(found, 1);

						}


                     
							if (split.find(".") != string::npos)
							{

								temp = split.substr(0, split.size() - 2);
								temp = temp + " " + split.substr(split.size() - 2);
							}
							else
								temp = split + " " + (*(iter + 1));
				

							pos = temp.find("_");

							if (pos != string::npos)
								temp.pop_back();


							for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
							{
								if ((*it).playername == temp)
								{
									(*it).IsHeOnCourt = true;
									cnt2 = 1;
								}
							}

							if (cnt2 == 0)
							{
								StructObj.push_back(player());
								StructObj.back().playername = temp;
								StructObj.back().team = strVec.at(0);
								StructObj.back().IsHeOnCourt = true;



							}

					}
					cnt2 = 0;
				}

				offset = -2;


				std::cout << teams[0] << "\t";
				std::cout << teams[1] << "\t";
				std::cout << quarter << endl;



				Player_List_Home_Team = "";
				Player_List_Away_Team = "";


				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{

			

					if ((*it).IsHeOnCourt) {
						if ((*it).team == teams[0])
							Player_List_Home_Team = Player_List_Home_Team + (*it).playername + ";";
						else if ((*it).team == teams[1])
							Player_List_Away_Team = Player_List_Away_Team + (*it).playername + ";";

					}



				}



			}
			// Second-Third and fourth Quarter Lineup Berechnung  End



			// Start FGM Berechnung
			pos = str.find("made");
			if (pos != string::npos)
			{

				pos = str.find("2PtsFG");
				if (pos != string::npos)
				{
					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{

						Game_Time = strVec.at(0);

						if (Game_Time.find(":") == std::string::npos) {
							Game_Time = "-";
						}

						if (*(it) == "2PtsFG")
						{

							temp = *(it - 1);

							if (temp.substr(temp.size() - 1) == "_")
								temp = temp.substr(0, temp.size() - 1);


							if (temp.size() > 2 && temp.find(".") != string::npos)
							{

								split = temp.substr(0, temp.size() - 2);

								while (split.find_first_not_of("~=_-|0123456789"))
								{
									found = split.find_first_of("~_=-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp.substr(temp.size() - 2);
							}
							else
							{
								split = *(it - 2);

								if (split.size() > 3)
								{
									while (split.find_first_not_of("~_-=|0123456789"))
									{
										found = split.find_first_of("~_-=|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp;
								}


							}


						}
					}


					
					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();




					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{
						if ((*it).playername == temp)
						{
							(*it)._2PM = 1;
							(*it).PTS = 2;
							team = (*it).team;
					

						}
					}



				}


				pos_2 = str.find("3PtsFG");
				if (pos_2 != string::npos)
				{

					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{

						Game_Time = strVec.at(0);

						if (Game_Time.find(":") == std::string::npos) {
							Game_Time = "-";
						}

						if (*(it) == "3PtsFG")
						{

							temp = *(it - 1);



							if (temp.size() > 2 && temp.find(".") != string::npos)
							{

								split = temp.substr(0, temp.size() - 2);

								while (split.find_first_not_of("~=_-|0123456789"))
								{
									found = split.find_first_of("~_=-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp.substr(temp.size() - 2);
							}						
							else
							{
								split = *(it - 2);

								while (split.find_first_not_of("~_-=|0123456789"))
								{
									found = split.find_first_of("~_-=|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp;

							}


						}
					}


					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();


					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{
						if ((*it).playername == temp)
						{
							(*it)._3PM = 1;
							(*it).PTS = 3;
							team = (*it).team;
			
						}
					}


				}


			}
			// End FGM Berechnung



		//Start 2PA Berechnung
			pos = str.find("2PtsFG");
			if (pos != string::npos)
			{
				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
				{

					if (*it == "2PtsFG")
					{
						temp = *(it - 1);

						if (temp.substr(temp.size() - 1) == "_")
							temp = temp.substr(0, temp.size() - 1);

						if (temp.size() > 2 && temp.find(".") != string::npos)
						{
							split = temp.substr(0, temp.size() - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp.substr(temp.size() - 2);
						}
						else if (temp.find(".") != string::npos)
						{
							split = *(it - 2);

							if (split.size() > 3)
							{
								while (split.find_first_not_of("~_-=|0123456789"))
								{
									found = split.find_first_of("~_-=|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp;
							}


						}


					}

				}



				pos = temp.find("_");

				if (pos != string::npos)
					temp.pop_back();



				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).playername == temp)
					{
						(*it)._2PA = 1;
						team = (*it).team;
			


						outfile << date << ",";
						outfile << teams[0] << ",";
						outfile << teams[1] << ",";
						outfile << quarter << ",";
						outfile << (*it).playername << ",";
						outfile << team << ",";
						outfile << (*it).PTS << ",";
						outfile << (*it).OfReb << ",";
						outfile << (*it).DefReb << ",";
						outfile << (*it)._2PM << ",";
						outfile << (*it)._2PA << ",";
						outfile << (*it)._3PM << ",";
						outfile << (*it)._3PA << ",";
						outfile << (*it).FTM << ",";
						outfile << (*it).FTA << ",";
						outfile << (*it).To << ",";
						outfile << (*it).Ast << ",";
						outfile << (*it).Blk << ",";
						outfile << (*it).St << ",";
						outfile << (*it).PF << ",";
						outfile << (*it).OF << ",";
						outfile << Sub_in << ",";
						outfile << Sub_out << ",";
						outfile << Game_Time << ",";
						outfile << Player_List_Home_Team << ",";
						outfile << Player_List_Away_Team << ",";
						outfile << "NULL" << ",";
						outfile << "NULL";
						outfile << endl;

						(*it).PTS = 0;
						(*it)._2PA = 0;
						(*it)._2PM = 0;
					}
				}



			}
			//End 2PA Berechnung



			//Start 3PA Berechnung
			pos_2 = str.find("3PtsFG");
			if (pos_2 != string::npos)
			{


					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					Game_Time = strVec.at(0);

					if (Game_Time.find(":") == std::string::npos) {
						Game_Time = "-";
					}


					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{

						if (*it == "3PtsFG")
						{
							temp = *(it - 1);

							if (temp.substr(temp.size() - 1) == "_")
								temp = temp.substr(0, temp.size() - 1);

							if (temp.size() > 2 && temp.find(".") != string::npos)
							{
								split = temp.substr(0, temp.size() - 2);

								while (split.find_first_not_of("=~_-|0123456789"))
								{
									found = split.find_first_of("=~_-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp.substr(temp.size() - 2);
							}				
							else if (temp.find(".") != string::npos)
							{
								split = *(it - 2);

								while (split.find_first_not_of("=~_-|0123456789"))
								{
									found = split.find_first_of("=~_-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp;

							}


						}
					}



					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{
						if ((*it).playername == temp)
						{
							(*it)._3PA = 1;
							team = (*it).team;
							


							outfile << date << ",";
							outfile << teams[0] << ",";
							outfile << teams[1] << ",";
							outfile << quarter << ",";
							outfile << (*it).playername << ",";
							outfile << team << ",";
							outfile << (*it).PTS << ",";
							outfile << (*it).OfReb << ",";
							outfile << (*it).DefReb << ",";
							outfile << (*it)._2PM << ",";
							outfile << (*it)._2PA << ",";
							outfile << (*it)._3PM << ",";
							outfile << (*it)._3PA << ",";
							outfile << (*it).FTM << ",";
							outfile << (*it).FTA << ",";
							outfile << (*it).To << ",";
							outfile << (*it).Ast << ",";
							outfile << (*it).Blk << ",";
							outfile << (*it).St << ",";
							outfile << (*it).PF << ",";
							outfile << (*it).OF << ",";
							outfile << Sub_in << ",";
							outfile << Sub_out << ",";
							outfile << Game_Time << ",";
							outfile << Player_List_Home_Team << ",";
							outfile << Player_List_Away_Team << ",";
							outfile << "NULL" << ",";
							outfile << "NULL";
							outfile << endl;

							(*it).PTS = 0;
							(*it)._3PA = 0;
							(*it)._3PM = 0;
						}
					}


					
				
			}
			//End 3PA Berechnung



			//Start FTA and FTM Berechnung
			pos = str.find("Free Throw");
			if (pos != string::npos)
			{


					pos_2 = str.find("missed");
					if (pos_2 == string::npos)
						cntFTM = true;


					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					if (strVec.at(0) != "Free") {

						for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
						{

							Game_Time = strVec.at(0);

							if (Game_Time.find(":") == std::string::npos) {
								Game_Time = "-";
							}



							if (*it == "Free")
							{
								temp = *(it - 1);


								if (temp.size() > 2 && temp.find(".") != string::npos)
								{
									split = temp.substr(0, temp.size() - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp.substr(temp.size() - 2);
								}
								else
								{
									split = *(it - 2);

									while (split.find_first_not_of("~_=-|0123456789"))
									{
										found = split.find_first_of("~_=-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp;

								}

							}
						}


						pos = temp.find("_");

						if (pos != string::npos)
							temp.pop_back();



						for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
						{
							if ((*it).playername == temp)
							{
								(*it).FTA = 1;
								team = (*it).team;

								if (cntFTM) {
									(*it).FTM = 1;
									(*it).PTS = 1;
								}

								outfile << date << ",";
								outfile << teams[0] << ",";
								outfile << teams[1] << ",";
								outfile << quarter << ",";
								outfile << (*it).playername << ",";
								outfile << team << ",";
								outfile << (*it).PTS << ",";
								outfile << (*it).OfReb << ",";
								outfile << (*it).DefReb << ",";
								outfile << (*it)._2PM << ",";
								outfile << (*it)._2PA << ",";
								outfile << (*it)._3PM << ",";
								outfile << (*it)._3PA << ",";
								outfile << (*it).FTM << ",";
								outfile << (*it).FTA << ",";
								outfile << (*it).To << ",";
								outfile << (*it).Ast << ",";
								outfile << (*it).Blk << ",";
								outfile << (*it).St << ",";
								outfile << (*it).PF << ",";
								outfile << (*it).OF << ",";
								outfile << Sub_in << ",";
								outfile << Sub_out << ",";
								outfile << Game_Time << ",";
								outfile << Player_List_Home_Team << ",";
								outfile << Player_List_Away_Team << ",";
								outfile << "NULL" << ",";
								outfile << "NULL";
								outfile << endl;




								(*it).PTS = 0;
								(*it).FTA = 0;
								(*it).FTM = 0;

							}
						}


						cntFTM = false;
					}
				

				time_temp = Game_Time;

			}
			//End FTA and FTM Berechnung



			//Start Blocked Shots Berechnung
			pos = str.find("Blocked");
			if (pos != string::npos)
			{
				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
				{

					if (*it == "Blocked")
					{
						temp = *(it - 1);


						if (temp.size() > 2 && temp.find(".") != string::npos)
						{
							split = temp.substr(0, temp.size() - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp.substr(temp.size() - 2);
						}
						else if (temp.find(".") != string::npos)
						{
							split = *(it - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp;

						}


					}
				}




				pos = temp.find("_");

				if (pos != string::npos)
					temp.pop_back();



				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).playername == temp)
					{
						(*it).Blk = 1;
						team = (*it).team;


						outfile << date << ",";
						outfile << teams[0] << ",";
						outfile << teams[1] << ",";
						outfile << quarter << ",";
						outfile << (*it).playername << ",";
						outfile << team << ",";
						outfile << (*it).PTS << ",";
						outfile << (*it).OfReb << ",";
						outfile << (*it).DefReb << ",";
						outfile << (*it)._2PM << ",";
						outfile << (*it)._2PA << ",";
						outfile << (*it)._3PM << ",";
						outfile << (*it)._3PA << ",";
						outfile << (*it).FTM << ",";
						outfile << (*it).FTA << ",";
						outfile << (*it).To << ",";
						outfile << (*it).Ast << ",";
						outfile << (*it).Blk << ",";
						outfile << (*it).St << ",";
						outfile << (*it).PF << ",";
						outfile << (*it).OF << ",";
						outfile << Sub_in << ",";
						outfile << Sub_out << ",";
						outfile << Game_Time << ",";
						outfile << Player_List_Home_Team << ",";
						outfile << Player_List_Away_Team << ",";
						outfile << "NULL" << ",";
						outfile << "NULL";
						outfile << endl;


						(*it).Blk = 0;

					}
				}

			}
			//End Blocked Shot Berechnung



			//Start Personal foul Berechnung
			pos = str.find("Personal");
			pos_2 = str.find("Unsportsmanlike");

			if (pos != string::npos || pos_2 != string::npos)
			{
				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
				{

					if (*it == "Personal" || *it == "Unsportsmanlike")
					{
						temp = *(it - 1);

						

						if (temp.size() > 2 && temp.find(".") != string::npos)
						{
							split = temp.substr(0, temp.size() - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp.substr(temp.size() - 2);
						}
						else if (temp.find(".") != string::npos)
						{
							split = *(it - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp;

						}


					}
				}


				pos = temp.find("_");

				if (pos != string::npos)
					temp.pop_back();



				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).playername == temp)
					{
						(*it).PF = 1;
						team = (*it).team;


						outfile << date << ",";
						outfile << teams[0] << ",";
						outfile << teams[1] << ",";
						outfile << quarter << ",";
						outfile << (*it).playername << ",";
						outfile << team << ",";
						outfile << (*it).PTS << ",";
						outfile << (*it).OfReb << ",";
						outfile << (*it).DefReb << ",";
						outfile << (*it)._2PM << ",";
						outfile << (*it)._2PA << ",";
						outfile << (*it)._3PM << ",";
						outfile << (*it)._3PA << ",";
						outfile << (*it).FTM << ",";
						outfile << (*it).FTA << ",";
						outfile << (*it).To << ",";
						outfile << (*it).Ast << ",";
						outfile << (*it).Blk << ",";
						outfile << (*it).St << ",";
						outfile << (*it).PF << ",";
						outfile << (*it).OF << ",";
						outfile << Sub_in << ",";
						outfile << Sub_out << ",";
						outfile << Game_Time << ",";
						outfile << Player_List_Home_Team << ",";
						outfile << Player_List_Away_Team << ",";
						outfile << "NULL" << ",";
						outfile << "NULL";
						outfile << endl;


						(*it).PF = 0;

					}
				}

			}
			//End Personal foul Berechnung




			//Start Offensive foul Berechnung
			pos = str.find("Offensive foul");
			if (pos != string::npos)
			{
				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
				{

					if (*it == "Offensive")
					{
						temp = *(it - 1);


						if (temp.size() > 2 && temp.find(".") != string::npos)
						{
							split = temp.substr(0, temp.size() - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp.substr(temp.size() - 2);
						}			
						else if (temp.find(".") != string::npos)
						{
							split = *(it - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp;

						}


					}
				}



				pos = temp.find("_");

				if (pos != string::npos)
					temp.pop_back();


		

				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).playername == temp)
					{
						(*it).PF = 1;
						(*it).OF = 1;
						team = (*it).team;


						outfile << date << ",";
						outfile << teams[0] << ",";
						outfile << teams[1] << ",";
						outfile << quarter << ",";
						outfile << (*it).playername << ",";
						outfile << team << ",";
						outfile << (*it).PTS << ",";
						outfile << (*it).OfReb << ",";
						outfile << (*it).DefReb << ",";
						outfile << (*it)._2PM << ",";
						outfile << (*it)._2PA << ",";
						outfile << (*it)._3PM << ",";
						outfile << (*it)._3PA << ",";
						outfile << (*it).FTM << ",";
						outfile << (*it).FTA << ",";
						outfile << (*it).To << ",";
						outfile << (*it).Ast << ",";
						outfile << (*it).Blk << ",";
						outfile << (*it).St << ",";
						outfile << (*it).PF << ",";
						outfile << (*it).OF << ",";
						outfile << Sub_in << ",";
						outfile << Sub_out << ",";
						outfile << Game_Time << ",";
						outfile << Player_List_Home_Team << ",";
						outfile << Player_List_Away_Team << ",";
						outfile << "NULL" << ",";
						outfile << "NULL";
						outfile << endl;


						(*it).PF = 0;
						(*it).OF = 0;

					}
				}

			}
			//End Offensive foul Berechnung



			//Start Technical foul Berechnung
			pos = str.find("Technical foul,");
			if (pos != string::npos)
			{
				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
				{

					if (*it == "Technical")
					{
						temp = *(it - 1);


						if (temp.size() > 2 && temp.find(".") != string::npos)
						{
							split = temp.substr(0, temp.size() - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp.substr(temp.size() - 2);
						}
						else if (temp.find(".") != string::npos)
						{
							split = *(it - 2);

							while (split.find_first_not_of("=~_-|0123456789"))
							{
								found = split.find_first_of("=~_-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp;

						}


					}
				}


		

				pos = temp.find("_");

				if (pos != string::npos)
					temp.pop_back();



				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).playername == temp)
					{
						(*it).PF = 1;
						team = (*it).team;


						outfile << date << ",";
						outfile << teams[0] << ",";
						outfile << teams[1] << ",";
						outfile << quarter << ",";
						outfile << (*it).playername << ",";
						outfile << team << ",";
						outfile << (*it).PTS << ",";
						outfile << (*it).OfReb << ",";
						outfile << (*it).DefReb << ",";
						outfile << (*it)._2PM << ",";
						outfile << (*it)._2PA << ",";
						outfile << (*it)._3PM << ",";
						outfile << (*it)._3PA << ",";
						outfile << (*it).FTM << ",";
						outfile << (*it).FTA << ",";
						outfile << (*it).To << ",";
						outfile << (*it).Ast << ",";
						outfile << (*it).Blk << ",";
						outfile << (*it).St << ",";
						outfile << (*it).PF << ",";
						outfile << (*it).OF << ",";
						outfile << Sub_in << ",";
						outfile << Sub_out << ",";
						outfile << Game_Time << ",";
						outfile << Player_List_Home_Team << ",";
						outfile << Player_List_Away_Team << ",";
						outfile << "NULL" << ",";
						outfile << "NULL";
						outfile << endl;



						(*it).PF = 0;

					}
				}

			}
			//End Technical foul Berechnung




		   // Start Defensive Rebound  Berechnung
			pos = str.find("Defensive rebound");
			if (pos != string::npos)
			{

					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					Game_Time = strVec.at(0);

					if (Game_Time.find(":") == std::string::npos) {
						Game_Time = "-";
					}

					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{

						if (*it == "Defensive")
						{

							temp = *(it - 1);

							

							if (temp.size() > 2 && temp.find(".") != string::npos)
							{
								split = temp.substr(0, temp.size() - 2);

								while (split.find_first_not_of("=~_-|0123456789"))
								{
									found = split.find_first_of("=~_-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp.substr(temp.size() - 2);
							}
							else
							{
								split = *(it - 2);

								while (split.find_first_not_of("=~_-|0123456789"))
								{
									found = split.find_first_of("=~_-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp;

							}


						}
					}
		

					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();


					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{
						if ((*it).playername == temp)
						{
							(*it).DefReb = 1;
							team = (*it).team;
				


							outfile << date << ",";
							outfile << teams[0] << ",";
							outfile << teams[1] << ",";
							outfile << quarter << ",";
							outfile << (*it).playername << ",";
							outfile << team << ",";
							outfile << (*it).PTS << ",";
							outfile << (*it).OfReb << ",";
							outfile << (*it).DefReb << ",";
							outfile << (*it)._2PM << ",";
							outfile << (*it)._2PA << ",";
							outfile << (*it)._3PM << ",";
							outfile << (*it)._3PA << ",";
							outfile << (*it).FTM << ",";
							outfile << (*it).FTA << ",";
							outfile << (*it).To << ",";
							outfile << (*it).Ast << ",";
							outfile << (*it).Blk << ",";
							outfile << (*it).St << ",";
							outfile << (*it).PF << ",";
							outfile << (*it).OF << ",";
							outfile << Sub_in << ",";
							outfile << Sub_out << ",";
							outfile << Game_Time << ",";
							outfile << Player_List_Home_Team << ",";
							outfile << Player_List_Away_Team << ",";
							outfile << "NULL" << ",";
							outfile << "NULL";
							outfile << endl;


							(*it).DefReb = 0;

						}
					}



			}



			pos = str.find("Defensive Team rebound");
			if (pos != string::npos)
			{

				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				outfile << date << ",";
				outfile << teams[0] << ",";
				outfile << teams[1] << ",";
				outfile << quarter << ",";
				outfile << "NULL" << ",";
				outfile << team << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 1 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << Game_Time << ",";
				outfile << Player_List_Home_Team << ",";
				outfile << Player_List_Away_Team << ",";
				outfile << "NULL" << ",";
				outfile << "NULL";
				outfile << endl;


			}
			// End Defensive Rebound Berechnung





			// Start Team Turnover Berechnung
			pos = str.find("Team Turnover,");
			if (pos != string::npos)
			{

				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				outfile << date << ",";
				outfile << teams[0] << ",";
				outfile << teams[1] << ",";
				outfile << quarter << ",";
				outfile << "NULL" << ",";
				outfile << team << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 1 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << 0 << ",";
				outfile << Game_Time << ",";
				outfile << Player_List_Home_Team << ",";
				outfile << Player_List_Away_Team << ",";
				outfile << "NULL" << ",";
				outfile << "NULL";
				outfile << endl;


			}
			// End Team Turnover Berechnung




			// Start Offensive Rebound Berechnung
			pos = str.find("Offensive rebound");
			if (pos != string::npos)
			{

				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));


					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					
						Game_Time = strVec.at(0);

						if (Game_Time.find(":") == std::string::npos) {
							Game_Time = "-";
						}


						for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
						{

							if (*it == "Offensive")
							{
								temp = *(it - 1);


								if (temp.size() > 2 && temp.find(".") != string::npos)
								{
									split = temp.substr(0, temp.size() - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp.substr(temp.size() - 2);
								}						
								else
								{
									split = *(it - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp;

								}


							}

						}


					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();



					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{
						if ((*it).playername == temp)
						{
							(*it).OfReb = 1;
							team = (*it).team;
				

							outfile << date << ",";
							outfile << teams[0] << ",";
							outfile << teams[1] << ",";
							outfile << quarter << ",";
							outfile << (*it).playername << ",";
							outfile << team << ",";
							outfile << (*it).PTS << ",";
							outfile << (*it).OfReb << ",";
							outfile << (*it).DefReb << ",";
							outfile << (*it)._2PM << ",";
							outfile << (*it)._2PA << ",";
							outfile << (*it)._3PM << ",";
							outfile << (*it)._3PA << ",";
							outfile << (*it).FTM << ",";
							outfile << (*it).FTA << ",";
							outfile << (*it).To << ",";
							outfile << (*it).Ast << ",";
							outfile << (*it).Blk << ",";
							outfile << (*it).St << ",";
							outfile << (*it).PF << ",";
							outfile << (*it).OF << ",";
							outfile << Sub_in << ",";
							outfile << Sub_out << ",";
							outfile << Game_Time << ",";
							outfile << Player_List_Home_Team << ",";
							outfile << Player_List_Away_Team << ",";
							outfile << "NULL" << ",";
							outfile << "NULL";
							outfile << endl;



							(*it).OfReb = 0;

						}

					}

			}




			//Start Turnover Berechnung 
			pos = str.find("Turnover,");
			if (pos != string::npos)
			{


					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

					Game_Time = strVec.at(0);

					if (Game_Time.find(":") == std::string::npos) {
						Game_Time = "-";
					}


					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{

						if (*it == "Turnover,")
						{
							temp = *(it - 1);

							

							if (temp == "Team") {
								cnt2 = 1;
								Game_Time = "-";
							}
							else if (temp.size() > 2 && temp.find(".") != string::npos)
							{
								split = temp.substr(0, temp.size() - 2);

								while (split.find_first_not_of("~=_-|0123456789"))
								{
									found = split.find_first_of("~=_-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp.substr(temp.size() - 2);
							}
							else
							{
								split = *(it - 2);

								while (split.find_first_not_of("~_=-|0123456789"))
								{
									found = split.find_first_of("~=_-|0123456789");
									split.erase(found, 1);

								}

								temp = split + " " + temp;

							}

						}

					}



				
					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();



					if (cnt2 == 0) {
						for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
						{
							if ((*it).playername == temp)
							{
								(*it).To = 1;
								team = (*it).team;



								outfile << date << ",";
								outfile << teams[0] << ",";
								outfile << teams[1] << ",";
								outfile << quarter << ",";
								outfile << (*it).playername << ",";
								outfile << team << ",";
								outfile << (*it).PTS << ",";
								outfile << (*it).OfReb << ",";
								outfile << (*it).DefReb << ",";
								outfile << (*it)._2PM << ",";
								outfile << (*it)._2PA << ",";
								outfile << (*it)._3PM << ",";
								outfile << (*it)._3PA << ",";
								outfile << (*it).FTM << ",";
								outfile << (*it).FTA << ",";
								outfile << (*it).To << ",";
								outfile << (*it).Ast << ",";
								outfile << (*it).Blk << ",";
								outfile << (*it).St << ",";
								outfile << (*it).PF << ",";
								outfile << (*it).OF << ",";
								outfile << Sub_in << ",";
								outfile << Sub_out << ",";
								outfile << Game_Time << ",";
								outfile << Player_List_Home_Team << ",";
								outfile << Player_List_Away_Team << ",";
								outfile << "NULL" << ",";
								outfile << "NULL";
								outfile << endl;


								(*it).To = 0;

							}
						}



					}



					cnt2 = 0;

				
			}
			//End Turnover Berechnung 




			//Start Assist Berechnung 
			pos = str.find("Assist");
			if (pos != string::npos)
			{


				found = str.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
				if (found != 0)
					boost::trim_if(str, boost::is_any_of("\t "));

			
					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);


					Game_Time = strVec.at(0);

					if (Game_Time.find(":") == std::string::npos) {
						Game_Time = "-";
					}


					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{


						if (*it == "Assist")
						{
							temp = *(it - 1);

							if (temp.substr(temp.size() - 1) == "_")
								temp = temp.substr(0, temp.size() - 1);


							if (temp.size() > 2 && temp.find(".") != string::npos)
							{
								
									split = temp.substr(0, temp.size() - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp.substr(temp.size() - 2);
							}	
								else
								{
									split = *(it - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp;

								}
							

						}
					}


		
					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();




					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{
						if ((*it).playername == temp) {
							(*it).Ast = 1;


							outfile << date << ",";
							outfile << teams[0] << ",";
							outfile << teams[1] << ",";
							outfile << quarter << ",";
							outfile << (*it).playername << ",";
							outfile << (*it).team << ",";
							outfile << (*it).PTS << ",";
							outfile << (*it).OfReb << ",";
							outfile << (*it).DefReb << ",";
							outfile << (*it)._2PM << ",";
							outfile << (*it)._2PA << ",";
							outfile << (*it)._3PM << ",";
							outfile << (*it)._3PA << ",";
							outfile << (*it).FTM << ",";
							outfile << (*it).FTA << ",";
							outfile << (*it).To << ",";
							outfile << (*it).Ast << ",";
							outfile << (*it).Blk << ",";
							outfile << (*it).St << ",";
							outfile << (*it).PF << ",";
							outfile << (*it).OF << ",";
							outfile << Sub_in << ",";
							outfile << Sub_out << ",";
							outfile << Game_Time << ",";
							outfile << Player_List_Home_Team << ",";
							outfile << Player_List_Away_Team << ",";
							outfile << "NULL" << ",";
							outfile << "NULL";
							outfile << endl;


							(*it).Ast = 0;

						}
					}


				


			}
			//End Assist Berechnung 



			//Start Steal Berechnung 
			pos = str.find("Steal");
			if (pos != string::npos)
			{

				boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);

				Game_Time = strVec.at(0);

				if (Game_Time.find(":") == std::string::npos) {
					Game_Time = "-";
				}


				for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
				{
					if (*it == "Steal")
					{
						temp = *(it - 1);


						if (temp.size() > 2 && temp.find(".") != string::npos)
						{
							split = temp.substr(0, temp.size() - 2);

							while (split.find_first_not_of("~=_-|0123456789O"))
							{
								found = split.find_first_of("~=_-|0123456789O");
								split.erase(found, 1);

							}

							temp = split + " " + temp.substr(temp.size() - 2);
						}
						else
						{
							split = *(it - 2);

							while (split.find_first_not_of("~_=-|0123456789"))
							{
								found = split.find_first_of("~_=-|0123456789");
								split.erase(found, 1);

							}

							temp = split + " " + temp;

						}


					}

				}




				pos = temp.find("_");

				if (pos != string::npos)
					temp.pop_back();



				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).playername == temp) {
						(*it).St = 1;


						outfile << date << ",";
						outfile << teams[0] << ",";
						outfile << teams[1] << ",";
						outfile << quarter << ",";
						outfile << (*it).playername << ",";
						outfile << (*it).team << ",";
						outfile << (*it).PTS << ",";
						outfile << (*it).OfReb << ",";
						outfile << (*it).DefReb << ",";
						outfile << (*it)._2PM << ",";
						outfile << (*it)._2PA << ",";
						outfile << (*it)._3PM << ",";
						outfile << (*it)._3PA << ",";
						outfile << (*it).FTM << ",";
						outfile << (*it).FTA << ",";
						outfile << (*it).To << ",";
						outfile << (*it).Ast << ",";
						outfile << (*it).Blk << ",";
						outfile << (*it).St << ",";
						outfile << (*it).PF << ",";
						outfile << (*it).OF << ",";
						outfile << Sub_in << ",";
						outfile << Sub_out << ",";
						outfile << Game_Time << ",";
						outfile << Player_List_Home_Team << ",";
						outfile << Player_List_Away_Team << ",";
						outfile << "NULL" << ",";
						outfile << "NULL";
						outfile << endl;


						(*it).St = 0;



					}

				}

			}
			//End Steal Berechnung 



			   // Start Substitutions
			pos = str.find("Substitute");
			if (pos != string::npos)
			{
				cnt2 = 0;

			

					boost::algorithm::split(strVec, str, is_any_of("\t "), boost::token_compress_on);


					Game_Time = strVec.at(0);

					if (Game_Time.find(":") == std::string::npos) {
						Game_Time = "-";
					}

					for (vector<string>::iterator it = strVec.begin(); it != strVec.end(); it++)
					{


						if (*it == "Substitute")
							if (cnt2 == 0)     // Substitute out 
							{

								temp = *(it - 1);


								if (temp.size() > 2 && temp.find(".") != string::npos)
								{
									split = temp.substr(0, temp.size() - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp.substr(temp.size() - 2);
								}
								else
								{

									split = *(it - 2);

									while (split.find_first_not_of("=~_-0123456789"))
									{
										found = split.find_first_of("=~_-0123456789");
										split.erase(found, 1);

									}

									temp = split + " " + temp;

								}

								cnt2 = 1;

							}
							else     // Substitute in 
							{
								temp2 = *(it - 1);


								if (temp2.size() > 2 && temp2.find(".") != string::npos)
								{
									split = temp2.substr(0, temp2.size() - 2);

									while (split.find_first_not_of("=~_-|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp2 = split + " " + temp2.substr(temp2.size() - 2);
								}
								else {

									split = *(it - 2);

									while (split.find_first_not_of("-=~_|0123456789"))
									{
										found = split.find_first_of("=~_-|0123456789");
										split.erase(found, 1);

									}

									temp2 = split + " " + temp2;
								}



							}

					}



					pos = temp.find("_");

					if (pos != string::npos)
						temp.pop_back();



					pos = temp2.find("_");

					if (pos != string::npos)
						temp2.pop_back();



					for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
					{

						if ((*it).playername == temp)   // Substitute out 
						{
							(*it).IsHeOnCourt = false;
							team = (*it).team;

						}


						if ((*it).playername == temp2)    // Substitute in 
						{
							IsHeOnCourt = true;
							(*it).IsHeOnCourt = true;

						}

					}



					if (!IsHeOnCourt)     // if player appears for the first time in the court
					{
						StructObj.push_back(player());
						StructObj.back().playername = temp2;
						StructObj.back().team = team;
						StructObj.back().IsHeOnCourt = true;


					}


					IsHeOnCourt = false;


					Sub_in = false;
					Sub_out = true;


					outfile << date << ",";
					outfile << teams[0] << ",";
					outfile << teams[1] << ",";
					outfile << quarter << ",";
					outfile << temp << ",";
					outfile << team << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << Sub_in << ",";
					outfile << Sub_out << ",";
					outfile << Game_Time << ",";
					outfile << "NULL" << ",";
					outfile << "NULL" << ",";
					outfile << "NULL" << ",";
					outfile << "NULL";
					outfile << endl;



					Sub_out = false;
					Sub_in = true;


					outfile << date << ",";
					outfile << teams[0] << ",";
					outfile << teams[1] << ",";
					outfile << quarter << ",";
					outfile << temp2 << ",";
					outfile << team << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << 0 << ",";
					outfile << Sub_in << ",";
					outfile << Sub_out << ",";
					outfile << Game_Time << ",";
					outfile << "NULL" << ",";
					outfile << "NULL" << ",";
					outfile << "NULL" << ",";
					outfile << "NULL";
					outfile << endl;


					Sub_out = false;
					Sub_in = false;


				cnt2 = 0;


				Player_List_Home_Team = "";
				Player_List_Away_Team = "";


				for (vector<player>::iterator it = StructObj.begin(); it != StructObj.end(); it++)
				{
					if ((*it).IsHeOnCourt) {
						if ((*it).team == teams[0])
							Player_List_Home_Team = Player_List_Home_Team + (*it).playername + ";";
						else if ((*it).team == teams[1])
							Player_List_Away_Team = Player_List_Away_Team + (*it).playername + ";";

					}
				}


			}
			// End Substitutions




		} // End getline loop


		cnt = 0;
		date = "NULL";
		StructObj.clear();

		// outfile.close();

		infile.close();

	}  // End read file loop


	outfile.close();


	return 0;
}

