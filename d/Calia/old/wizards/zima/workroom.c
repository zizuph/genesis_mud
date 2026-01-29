inherit "/std/workroom";
#include "/d/Calia/abbrev.h"
 
void
create_workroom()
{
    set_short("Zima's chambers");
 
    set_long(break_string(
        "These darkened chambers are the mystical haunts of Zima the " +
        "Hierophant of Argos.  The chamber is constructed of black marble " +
        "in the shape of a triangle pointing south.  A large crystal dome " +
        "caps the chamber, mysterious light filtering through its " +
        "mosaic.  In the center of the room is an altar, a triangular " +
        "column of black obsidian, upon which rests a grecian lamp, its " +
        "flickering flame giving a subtle light to the room.  A " +
        "mysterious symbol is crafted of ivory into the floor, following " +
        "the triangular edges of the walls.  Arched passageways in the " +
        "center of each wall, marked by doorways made of intricately " +
        "engraved silver, lead into other chambers.  A solemn " +
        "peace lingers here, a place for meditation and thought.\n",70));
 
    add_item(({"dome","mosaic"}), break_string(
        "A flat dome is centered in the ceiling of the chamber, a mosaic " +
        "of crystal crafted into a white rose with eleven petals and " +
        "four sepals.  A mysterious light filters through the dome, " +
        "giving you a sense of a divine presence as you stare upwards into " +
        "its heights.\n",70));
 
    add_item("altar", break_string(
        "A simple triangular altar of black obsidian, it seems to rise " +
        "out of the black marble floor.  A grecian lamp sits on top " +
        "of the altar, making it the focal point of the chamber.\n",70));
 
    add_item("lamp", break_string(
        "An oblong bowl-shaped lamp, with a handle on one end and a " +
        "wick on the other, this golden vessel is intricately detailed " +
        "and gives life to the dancing flame on its end.  A feeling of " +
        "peace and wisdom comes over you as are enchanted by its light.\n",70));
 
    add_item("symbol", break_string(
        "Crafted into the black marble floor, this symbol made of ivory " +
        "looks somewhat " +
        "like the numeral seven, outlining the chamber along the walls " +
        "except for a break in its line along the southwest.\n",70));
 
    add_item("passageways", break_string(
        "Arched entrances to the other parts of Zima's abode, they are " +
        "framed by doorways of engraved silver.\n",70));
 
    add_item("doorways", break_string(
        "Framing the passageways leading to other chambers, these doorways " +
        "are made of shining silver, mysterious runes engraved along their " +
        "edges which you can not read.\n",70));
 
    add_exit("/d/Calia/zima/workrm/meet","southwest",0);
    add_exit("/d/Calia/zima/workrm/study","southeast",0);
    add_exit("/d/Calia/zima/workrm/foyer","north",0);
 
}
 
