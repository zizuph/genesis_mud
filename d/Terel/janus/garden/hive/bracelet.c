/*  bracelet.c */
/*  janus 920831 */
/*
 * Lucius - Jan 2021
 *    Cleaned up and modernized.
 */
inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

public void
create_object()
{
    set_name("bracelet");
    set_adj("onyx");
    set_long(
	"An onyx bracelet. There are carved figures in the small " +
	"bracelet. All the figures seems to be of people involved "+
	"with gardening duties. It seems to be slightly "+
	"damaged such that you cannot wear it. It is the "+
	"locking mechanism that is damaged, thus it just "+
	"keeps falling off.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,  100);
    add_prop(OBJ_M_NO_DROP,  0);
    add_prop(OBJ_I_NO_GET,   0);
}
