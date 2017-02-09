#include <iostream>
#include <string>

using namespace std;

#include "hashMap.cpp"
//#include "hashMapTraining.cpp"

size_t stringToHash(const string& s,size_t size)
{
	size_t result = 0;

	for(char x : s)
	{
		result += x;
	}

	return result % size;
}

void addHundred(double& num)
{
	num += 100.0;
}

void testHashMap()
{
	HashMap<string,double> hmap(7,stringToHash);

	hmap["Nick"] = 1.76;
	hmap["Rey"] = 1.83;

	assert(hmap["Nick"] == 1.76);
	assert(hmap.containsKey("Rey") == true);
	assert(hmap.containsKey("Peter") == false);

	hmap.map(addHundred);

	assert(hmap["Nick"] == 101.76);
}

void testHashMapCanonical()
{
	HashMap<string,double> hmap(7,stringToHash);

	hmap["John"] = 1.70;
	hmap["Wayne"] = 1.77;

	HashMap<string,double> hmap2(hmap);
	assert(hmap2["John"] == 1.70);
	assert(hmap2.containsKey("Wayne") == true);
	assert(hmap2.containsKey("Patrik") == false);

	hmap["Ryan"] = 1.81;
	assert(hmap2.containsKey("Ryan") == false);

	hmap2 = hmap;
	assert(hmap2.containsKey("Ryan") == true);

}

int main()
{
	testHashMap();
	testHashMapCanonical();
	cout<<"So lame,you've passed it."<<endl;
}
