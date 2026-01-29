/* common code for the domain tower rooms  */
/* Tech the toolmaker came up with this piece of code 91-10-06 */

#include <stdproperties.h>
#define DIR_ITEMS	4
string	level_name;
string	up;
string	up_fun;
string	down;
string	down_fun;
string	*dirs;

void	setup_func();

void
create_room() 
{
	string long;
	int	i;
	object	ob;

	setup_func();

	long = "Tower of Domains level " + level_name + ".\n";

	for(i=0; i < sizeof(dirs); i += DIR_ITEMS) {

		ob = get_domain_lord(dirs[i+2]);

		long += "To the " + dirs[i] + " is the domain of"
			+ dirs[i+1] + dirs[i+2];
		if (!ob)
		    long += " without any lord.\n";
		else {
		    long += " with the mighty liege "
			+ capitalize( (string) ob->query_real_name()) + ".\n";
		    ob->remove_object();
		}

	}

	long += "Above and below you the tower continues....\n";

	set_short("Tower of Domains level " + level_name);

	set_long(long);

	add_exit(THIS_DIR + up, "up", up_fun);
	add_exit(THIS_DIR + down, "down", down_fun);

	for(i=0; i < sizeof(dirs); i += DIR_ITEMS) {
		add_exit("/d/" + dirs[i+2] + "/common/domain_entr",
			dirs[i+0], dirs[i+3]);
	}
	change_prop(ROOM_I_LIGHT, 10);
}
