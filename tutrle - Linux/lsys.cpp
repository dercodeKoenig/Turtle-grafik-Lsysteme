

namespace lsys{

	struct al{
		char in;
		std::string out;
	};


	struct ak{
		char in;
		std::string out;
	};
	std::vector<al> a;
	std::vector<ak> k;

	std::string mult(std::string in){
		std::string out;
		for(int i=0;i<in.size();i++){
			bool r=0;
			std::vector<std::string>estr;
			for(auto h:k){
				if(h.in==in[i]){
					estr.push_back(h.out);
					r=1;
				}
			}
			if(!r)out+=in[i];
			else{
				int ra=rand()%estr.size();
				out+=estr[ra];
			}
		}
		
		return out;
	}

	void def(char in, std::string out){
	al x;
	x.in=in;
	x.out=out;
	a.push_back(x);
	}
	void def_mult(char in, std::string out){
	ak x;
	x.in=in;
	x.out=out;
	k.push_back(x);
	}
	std::string parse(char in){
		std::string out;
		out+=in;
		for(auto i:a){
			if(i.in==in)
				out=i.out;
		}
	return out;
	}


	std::string mainfunc(std::string t2, int n){
		
	srand(time(0));
	std::string instring;
	std::string outstring;
	std::string tstring;
	
	std::string xstart;	
	std::string zeile;
	
	bool df=0;
	bool al=0;
	bool num=0;
	for(int i=0;i<t2.size();i++){
	
		if(t2[i]=='\n'){
			if(zeile=="#def"){
				df=1;
			}
			else if(zeile=="#end"){
				df=0;
				al=0;
			}
			else if(zeile==std::string("#rek")){
				num=1;
			}
			else if(zeile=="#al"){
				al=1;
			}
	
			else if(!al&&!df&&!num){
				xstart+=zeile;
				xstart+='\n';
			}
			else if(num&&n==0){
				n=atoi(zeile.c_str());
			}
			else if(al){
				std::string ze;
				char b;
				b=zeile[0];
				zeile.erase(zeile.begin());
				zeile.erase(zeile.begin());
				def(b,zeile);
			}
			else if(df){
				std::string ze;
				char b;
				b=zeile[0];
				zeile.erase(zeile.begin());
				zeile.erase(zeile.begin());
				def_mult(b,zeile);
			}
			
			zeile.clear();
		}
		else zeile+=t2[i];
	}
	
		std::string multstr=xstart;
		for(int i=0;i<n;i++){
			multstr=mult(multstr);
		}
	
	
		std::string t;
			t=multstr;
			t2.clear();
			for(int i=0;i<t.size();i++){
				t2+=parse(t[i]);
			}
	
	return t2;
	}	

}
