
inherit "/std/workroom";
#include "/d/Dville/abbrev.h"

void
create_workroom()
{
    set_short("Zima's chambers");
    set_long(BS(
        "\nThese darkened hallowed chambers are the mystical haunts of the " +
        "wizard Zima, the Madwand of Dville and Hierophant of Argos.\n\n"  +
        "The room is in a large triangular shape, constructed of black "   +
        "marble.  The floor is detailed in white ivory with a " +
        "white rose in the center, and a mysterious symbol which follows " +
        "the triangular edges of the chamber. " +
         "A shield emblazoned with a cruci-crescent hangs " +
        "on the north wall, behind which are two crossed swords, while the " +
        "southeastern wall is decorated with a banner intricately "        +
        "embroidered with a winged horse.\n\n" +
        "In the center of the chamber is a triangular altar,  a simple "   +
        "column of black obsidian, upon which is placed a golden grecian " +
        "lamp, whose mysterious dancing flame gives light to this "        +
        "peacefully solemn chamber.  Arched passages lead out of the " +
        "room on each wall.\n\n"));
    add_exit("/d/Dville/zima/workrm/stable","southwest",0);
    add_exit("/d/Dville/zima/workrm/study","southeast",0);
    add_exit("/d/Dville/zima/workrm/foyer","north",0);


   add_item(({"rose","white rose"}), BS(
      "Crafted of white ivory, this rose is portrayed with eleven " +
      "delicate petals and is centered in the floor of the chamber.\n"));

   add_item(({"symbol","mysterious symbol"}), BS(
      "Crafted of white ivory, this mysterious symbol traces the " +
      "triangular walls of the chamber, except for a discontinued " +
      "part on the southwestern wall, making the symbol look somewhat " +
      "like a triangular numeral seven.\n"));

   add_item("banner", BS(
      "This banner of royal blue, beautifully embroidered with a rampant " +
      "winged horse, is the symbol of the realm of Argos.\n"));

   add_item(({"lamp","grecian lamp"}), BS(
            "Made of pure gold and engraved with elegant lines, this lamp " +
            "is in the shape of an oblong bowl " +
           "with a handle on one side and a wick extension on the other. " +
           "An ornate lid covers the bowl, and an engraved base fans from " +
           "a short stem at the bottom.\n"));
   
   add_item("swords", BS(
      "Crafted with spiraling hilts, these swords hang crossed behind " +
      "the shield.\n"));

   add_item("shield", BS(
      "A golden shield emblazoned with a cruci-crescent.\n"));

   add_item("cruci-crescent", BS(
      "This mysterious symbol consists of an equi-armed cross, behind " +
      "which rises an elegant crescent moon.\n"));
}
