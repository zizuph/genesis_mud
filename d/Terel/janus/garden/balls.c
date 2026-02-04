/*  ball and chain */
/*  janus 920909 */
/*
    Modified: 6 May 2003, by Bleys
        - Updated includes and the inherit
        - Added a set_short, another adj and another name

    Modified: 1 Aug 2003, by Bleys
        - added _terel_egarden_punish_obj name to help Joe the
            gardener find this more easily when people want to
            pay the fine.

   Modified: 12 Now 2015, by Cherek
    - After complaints from newbies and wrong advice from older
      players I added the info that you can pay the fine to get
      rid of it to the long desc.

*/

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;
#include <stdproperties.h>
#include "/d/Terel/include/recover.h"

create_object()
{
  set_name("ball");
  add_name("chain");
  add_name("_terel_egarden_punish_obj");
  add_adj(({"heavy", "iron"}));
  set_short("ball and chain");
  set_long("This is a heavy iron ball attached to your foot with a chain. " +
           "It has a tag saying: 'If you want to get rid of this ball you need to pay " +
           "the fine - Joe, the gardener'.\n");
  add_prop(OBJ_I_WEIGHT,25000);
  add_prop(OBJ_I_VOLUME,1);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_M_NO_DROP, 1);
}


