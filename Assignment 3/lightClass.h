#include "Header.h"
#include "triple.h"

using namespace std;

class lightClass{
public:
	lightClass(void);

	lightClass(triple pos);

	void moveleft(void);

	void moveright(void);

	void moveforward(void);

	void movebackward(void);

	void moveup(void);

	void movedown(void);
	
	void switchOn (void);
private:
	triple pos;
	bool on = TRUE;
};