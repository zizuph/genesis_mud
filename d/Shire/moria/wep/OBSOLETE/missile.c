#include "defs.h"
#include "/d/Shire/moria/include/bows.h"

inherit "/std/object";

int missile_type;
int missile_hit;
int missile_pen;
int missile_quality;

nomask void
create_object()
{
    set_name("missile");
    this_object()->create_missile();
    if (missile_quality <= 0)
	missile_quality = 100;
}

void
set_missile_type(int type)
{
    missile_type = type;
}

int
query_missile_type()
{
    return missile_type;
}

void
set_missile_hit(int hit)
{
    missile_hit = hit;
}

int
query_missile_hit()
{
    return missile_hit;
}

void
set_missile_pen(int pen)
{
    missile_pen = pen;
}

int
query_missile_pen()
{
    return missile_pen;
}

void
set_missile_quality(int qual)
{
    missile_quality = qual;
}

int
query_missile_quality()
{
    return missile_quality;
}

int
reduce_quality(int amount)
{
    missile_quality -= amount;
    if (missile_quality <= 0)
	missile_quality = 0;
    return missile_quality;
}
