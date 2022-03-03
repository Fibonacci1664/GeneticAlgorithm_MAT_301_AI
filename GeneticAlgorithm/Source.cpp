#include "openGA.hpp"

#include <iostream>

std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.|!#$£%^&*()=+?@ 1234567890";
std::string target_string = "To be, or not to be.";

struct Chromosome
{
	std::string data;
};

struct Cost
{
	float score;
};

typedef EA::Genetic<Chromosome, Cost> GeneticAlgo;
typedef EA::GenerationType<Chromosome, Cost> GenerationType;

bool calculateCost(const Chromosome& individual, Cost& cost)
{
	// Create a score value that starts at 0
	// Iterate through the indivdual string and check for a match
	// For each mismatching pair, add the the score value
	// Assign the score value to the Cost objects cost value and return true

	float score = 0;

	for (int i = 0; i < individual.data.size(); ++i)
	{
		if (individual.data[i] != target_string[i])
		{
			++score;
		}
	}

	cost.score = score;

	return true;
}


char generate_random_character(const std::function<double(void)> &rnd01)
{
	return valid_chars[(int)(valid_chars.size() * rnd01())];
}

void shakespeare_init_genes(Chromosome& s, const std::function<double(void)> &rnd01)
{
	for (int i = 0; i < target_string.size(); i++)
	{
		s.data += generate_random_character(rnd01);
	}
}

double calculate_total_fitness(const GeneticAlgo::thisChromosomeType & X)
{
	return X.middle_costs.score;
}

int main()
{
	EA::Chronometer timer;
	timer.tic();

	GeneticAlgo ga_obj;
	ga_obj.problem_mode = EA::GA_MODE::SOGA;	// State the Genetic Algorithm is aiming for a single objective.
	ga_obj.population = 200;
	ga_obj.generation_max = 1000;				// We want this to keep attempting for a long time.
	ga_obj.init_genes = shakespeare_init_genes;
	ga_obj.calculate_SO_total_fitness = calculate_total_fitness;
	//ga_obj.eval_solution = ;
	//ga_obj.mutate = ;
	//ga_obj.crossover = ;
	ga_obj.crossover_fraction = 1;
	ga_obj.mutation_rate = 0.05;
	ga_obj.best_stall_max = 1000;
	ga_obj.average_stall_max = 1000;
	EA::StopReason reason = ga_obj.solve();

	std::cout << "The problem is optimized in " << timer.toc() << " seconds." << std::endl;

	std::cin.get();
}