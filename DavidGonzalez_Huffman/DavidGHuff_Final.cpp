 
// Huffman Tree algorithm, to run it, go in the last lines of code and input the text to code in the string huff text. We struct each node, with its internal info, and we will combine them, frecuency and chars until we get the root
// We create nodes, we compare the frecuencies, we set their position in the queue and create a priority queue.

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

// First we will declare an structure for the node, containing the character inside it, the frecuency and the position in the "tree"

struct Node  
{
	char ch;
	int freq; 
	
	Node *left, *right;
};

// This function will be used to allocate a new tree with its nodes ( with its position, the ch and the frecuency)

Node* createNode(char ch, int freq, Node* left, Node* right) {
	
	Node* node = new Node(); 

	node->ch = ch;
	node->freq = freq;
	
	node->left = left; 
	node->right = right;

	return node;             // This will assignt to each part of the structure of the node their values/characters
}

// Below we will use a comparation to compare each node to the node that will have the frequency, here we structure  compare for that
struct comparation
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};
// Here ocurrs the encode, to do that it will
// This will cross the huffmann tree and store each node in a map of the tree, adding a one or a 0 everytime a branch is ended in a node


void encoding(Node* root, string str, unordered_map<char, string> &huffCode){
	if (root == nullptr)    // The root node isnt an ending branch
		return;

	
	if (!root->left && !root->right) {   // This is an ending branch
		huffCode[root->ch] = str;
	}

	encoding(root->left, str + "0", huffCode);   // We run the function encode, and add a 0 to the string ( str ) if the node "goes" left
	encoding(root->right, str + "1", huffCode);   // we add a 1 if its right
}


     //Here ocurss the decode, that will cross the tree ( in a sorting way ) and will
// decode the encoded string . This function will be called later
void decoding(Node* root, int &i, string str){
	
	if (root == nullptr) {    // This node isnt an ending branch so the pointer is empty, and we check that 
		return;
	}

	
	if (!root->left && !root->right)  // This one is an ending because there are no roots on either side, so move the root to the character
	{
		cout << root->ch;    // If its an ending, show in the terminal the character saved in the root.
		return;
	}

	i++;

	if (str[i] =='0')
		decoding(root->left, i, str); // Move it to the left structure.data of the node, using the decoding function ( the one up of this one )
	else
		decoding(root->right, i, str);  // or the right one if is filled
}



// This will built the huffman tree and store it in an undordered map
	void buildTree(string hufftext)
	{

	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
		for (char ch: hufftext) {
		freq[ch]++;
	}

	// We will create a priority queue, since we have the std of queues, we can just define.
	
	 priority_queue<Node*, vector<Node*>, comparation> priority_queue;  

    // Then we will create an ending-branch node for each character to include it in the priority qeue

		for (auto pair: freq) {
		priority_queue.push(createNode(pair.first, pair.second, nullptr, nullptr));
	}


	while (priority_queue.size() != 1)   // Keep doing it if the size of the queue, are 2 or more nodes
	{
		
		Node *left = priority_queue.top(); priority_queue.pop();               // Take the nodes on the top of the priority queue ( and move it to node left and right)
		Node *right = priority_queue.top();	priority_queue.pop();        // And then move the next one

	
		int sum = left->freq + right->freq;     // Create a new bridge node that will have the frequency ( sum ) of both nodes as lower branches
		priority_queue.push(createNode('\0', sum, left, right));  // Use getnode to create a new node and add it to the priority
	}

	
	Node* root = priority_queue.top();      // Root here will save the main root of the Tree ( the top of the priority queue)

	
	unordered_map<char, string> huffCode;   // Will sort the map, and then use the encode function created before
	encoding(root, "", huffCode);

	cout << "Each Letter Code is :" << '\n';
	
	for (auto pair: huffCode) {
		cout << pair.first << " " << pair.second << '\n'; // I use pair to mix 2 values with diferent values, using auto pair:, the char and the int value
	}

	string str = "";
  for (char ch: hufftext) {
	
		str += huffCode[ch];
	}

	cout << '\n' <<"The string alredy coded is :"<< '\n' << str << '\n';

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	
	int i = -1;
	cout <<'\n' << "The string being decoded is:"<<'\n' ;             // Here crosses the Huffman Tree to decode the encoded string.
		while (i < (int)str.size() - 2) {         // While our string is less than the main one, keep doing the decode function
		decoding(root, i, str);         // Calling the decode function.
	}
}

////////////////////////////     MAIN        /////////////////////////7
// In the main, we create the string text and we run it and run the whole buildhuffmanTree.
int main() {
	
	string hufftext = "Drzewo, które pozostanie na liscie, jest nazywane drzewem Huffmana – prawdopodobienstwo zapisane w korzeniu jest równe 1, natomiast w lisciach drzewa zapisane sa symbole. Algorytm Huffmana jest algorytmem niedeterministycznym, poniewaz nie okresla, w jakiej kolejnosci wybierac drzewa z listy, jesli maja takie samo prawdopodobienstwo. Nie jest równiez okreslone, które z usuwanych drzew ma stac sie lewym badz prawym poddrzewem. Jednak bez wzgledu na przyjete rozwiazanie srednia dlugosc kodu pozostaje taka sama.";
	
	buildTree(hufftext);  // Runs the whole function.

	return 0;  
}
