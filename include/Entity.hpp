
using namespace std;


class Entity: public Object {
private:
	entity_t	data;

public:
	bool		fwrite		(int fd);
	
	Entity*		clone		(void);
};



