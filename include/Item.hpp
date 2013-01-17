
#include "types.h"

using namespace std;

class Item: public Object {
private:
	item_t		data;

public:
	bool	fwrite		(int fd);
	
	Item*	clone		(void);
};
