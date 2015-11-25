int
numerical_laplace()
{

	const int x_max = 49, y_max = 39;
	double v_top = 0.0, v_bottom = 0.0, v_left = 9.8, v_right = 0.0;
	int iterations = 1000;
	bool write_matrix_init = true;
	bool additional_constraints = true;
	bool write_matrix_final = false;
	bool output = true;
	bool plot = true;

	//Create array filled with 0's in the size of the grid + 2 (add boundary conitions)
	double laplace[x_max+2][y_max+2];
	for(int i = 0; i < x_max+2; i++)
	{
		for(int j = 0; j < y_max+2; j++)
		{
			laplace[i][j] = 0.0;
			if(i == 0) laplace[i][j] = v_left;
			if(j == 0 && i != 0) laplace[i][j] = v_bottom;
			if(i == x_max+1) laplace[i][j] = v_right;
			if(j == y_max+1 && i != 0) laplace[i][j] = v_top;
		}
	}
	cout << "Matrix Created." << endl;
	if(additional_constraints)
	{
		laplace[1][0] = v_left / 2;
		laplace[2][0] = v_left / 2;
		laplace[3][0] = v_left / 2;
		laplace[1][40] = v_left;
		laplace[2][40] = v_left / 2;
		laplace[3][40] = v_left / 2;
		laplace[4][40] = v_left / 4;
		cout << "    (additional Constraints applied)" << endl;
	}

	if(write_matrix_init == true)
	{
		for(int i = 0; i < x_max+2; i++)
		{
		cout << " | ";
			for(int j = 0; j < y_max+2; j++)
			{
				cout << laplace[i][j] << " | ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	
	for ( int k = 0; k < iterations; k++)
	{
		//Loop over all iterations, averaging each point with those around them... skipping over boundary conditions
//		cout << "Iteration: " << k << endl;
		for(int i = 1; i < x_max+1; i++)
		{
			for(int j = 1; j < y_max+1; j++)
			{
//				laplace[i][j] = 0.25*( laplace[i-1][j] + laplace[i+1][j] + laplace[i][j-1] + laplace[i][j+1] );
				laplace[i][j] = 0.125*( laplace[i-1][j] + laplace[i+1][j] + laplace[i][j-1] + laplace[i][j+1] + laplace[i-1][j-1] + laplace[i-1][j+1] + laplace[i+1][j-1] + laplace [i+1][j+1] );
			}
		}
	}

	cout << "Computations Completed. Plotting..." << endl;

	if(write_matrix_final == true)
	{
		for(int i = 0; i < x_max+2; i++)
		{
		cout << " | ";
			for(int j = 0; j < y_max+2; j++)
			{
				cout << laplace[i][j] << " | ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}

	//Write the output to a file
	if(output)
	{
		ofstream myfile;
		myfile.open("numerical_solution.txt");

		for(int i = 1; i < x_max+1; i++)
		{
			for(int j = 1; j < y_max+1; j++)
			{
				myfile << i << " " << j << " " << laplace[i][j] << endl;
//				myfile << j << " " << i << " " << laplace[i][j] << endl;
			}
		}
		myfile.close();	
		cout << "Output file created." << endl;
	}


	if(plot)
	{
		//Create the output graph
		TCanvas *c1 = new TCanvas();
		TGraph2D *gr = new TGraph2D();
		for(int i = 1; i < x_max+1; i++)
		{
			for(int j = 1; j < y_max+1; j++)
			{
				gr->SetPoint( gr->GetN(), i, j, laplace[i][j] );
			}
		}
		//gr->Draw("surf1");
		gr->Draw("COLZ");

		TCanvas *c2 = new TCanvas();
		gr->Draw("surf1");

	//	TH2 *h2 = gr->Project("xy");
	//	h2->Draw();
	}

	return 0;
}
