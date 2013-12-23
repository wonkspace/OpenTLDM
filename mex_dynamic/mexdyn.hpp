class MyData {

	public:
	  void display();
	  MyData(int handle=-1, int v1 = 0, int v2 = 0);
	  ~MyData() {}
	private:
	  int handle, val1, val2;
};
