inherit "/std/object";
#include "/d/Kalad/defs.h"

/*
 * This object should be inherited by every missile. Use set_hit and
 * set_pen to set the bonus hit and pen it will add to the missile 
 * launcher. It may not excceed 10/10 unless its a magical arrow.
 * Sarr 20.Jul.97
 *
 */

int pen;
int hit;
string mis_ty;

void
set_hit(int i)
{
    hit = i;
}

string
query_missile_type()
{
    return mis_ty;
}

void
set_missile_type(string str)
{
    mis_ty = str;
}

int
query_missile()
{
    return 1;
}
void
set_pen(int i)
{
    pen = i;
}

int
query_pen()
{
    return pen;
}

int
query_hit()
{
    return hit;
}

void
create_missile()
{
}


void
create_object()
{
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE,10);
    create_missile();
}
