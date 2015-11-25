#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

int
plotting_output()
{

	vector< int > x, y;
	vector< double > laplace;
	string mapping_tower_file = "./numerical_solution.txt";


	/* Stream to read table from file */
	ifstream istream_mapping;

	/* Open the datafile, if it won't open return an error */
	if (!istream_mapping.is_open())
	{
		istream_mapping.open( mapping_tower_file.c_str() );
		if(!istream_mapping)
		{
			cerr << "CaloTowerGeomManager::ReadGeometryFromTable - ERROR Failed to open mapping file " << mapping_tower_file << endl;
			exit(1);
		}
	}

	string line_mapping;
	int x_i, y_i;
	double laplace_i;

	while ( getline( istream_mapping, line_mapping ) )
	{
		istringstream iss(line_mapping);
		iss >> x_i >> y_i >> laplace_i;
		x.push_back( x_i );
		y.push_back( y_i );
		laplace.push_back( laplace_i );
	}

	TCanvas *c1 = new TCanvas();
	TGraph2D *gr = new TGraph2D();
	for(int i = 0; i < x.size(); i++)
	{
		gr->SetPoint( gr->GetN(), x.at(i), y.at(i), laplace.at(i) );
	}
	gr->Draw("surf1");
	cout << "graph drawn " << endl;

	TCanvas *c1 = new TCanvas();
	gr->Draw("P");





	return 0;
}
