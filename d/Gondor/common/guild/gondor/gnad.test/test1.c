/* test reading a large file via TP->more(read_file(file), 0) */

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"		/* always ... */

#define	TEST_NAME \
	"/d/Gondor/common/guild/gondor/gnad.test/book-of-votes.txt"

public void	create_gondor();
public void	init();
public int	readit(string arg);


public void
create_gondor()
{
    FIX_EUID;
    set_short("a test room");
    set_long("A test room -- trying 'readit' "+
	"will invoke TP->more(read_file(TEST_NAME), 0)\n"+
	"where TEST_NAME is \""+TEST_NAME+"\"\n");
}

public void
init()
{
    add_action(readit, "readit");
}

public int
readit(string arg)
{
    write("file_size(\""+TEST_NAME+"\") == "+file_size(TEST_NAME)+"\n");
    TP->more(read_file(TEST_NAME), 0);
    return 1;
}
