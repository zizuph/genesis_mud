/**
*** A pole with a pennant on it found in the depots of the chariot
*** transport. Players raise the pennant when they want a chariot.
***
*** Date      Coder      Action
*** ------- ----------- -----------------------------
*** 9/10/95   Zima       Created
***
**/
inherit "std/object";
#include <stdproperties.h>
 
int raised=0;
 
int  query_pennant() { return raised; }
void raise_pennant() { raised=1; }
void lower_pennant() { raised=0; }
 
void create_object() {
    set_name("pole");
    set_short("tall pole with a pennant");
    set_long("It is a very tall pole with a pennant flying from it. There "+
             "is a small inscription written on the pole.\n");
    add_item("pennant","@@exa_pennant");
    add_item("inscription",
       "It is written in small letters on the pole.\n");
    add_cmd_item("inscription","read",
       "It says: Raise the pennant when you need a chariot.\n");
 
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_INS, 1);
}
 
string exa_pennant() {
   if (!(raised)) return
      "It is a long blue pennant flying from the pole. It is lowered.\n";
   else return
      "It is a long blue pennant flying form the pole. It is raised.\n";
}
