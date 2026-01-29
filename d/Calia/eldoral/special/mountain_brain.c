#include "defs.h"

int horn;

public void
randomize_ruins()
{
    horn = random(17) + 1;
}

public string
query_ruin()
{
    return MOUNT + "m" + horn;
}
