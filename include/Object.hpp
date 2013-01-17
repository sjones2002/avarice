

class Object {
private:
	object_t 	data;
	
public:
	bool		fwrite		(int fd);
	
	Object*		clone		(void);
};
