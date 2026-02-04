inherit "std/room";
#define PATH "/d/Terel/common/town/garden/"

object monster;

reset_room(arg){
   
   if(!monster){
      monster=clone_object(PATH + "pilgrim");
      monster->move(this_object());
   }
}
create_room(){
   
   set_short("Clearing");
   set_long("A small clearing in the garden. A row of holly bushes\n" +
      "ring the area, their berries glistening in the light.\n" +
      "A pile of rocks stand here, like a cairn, upon which is\n" +
      "a silver star.\n");
   
   add_exit(PATH + "garden2", "west", 0);
   
   monster=clone_object(PATH + "pilgrim");
   monster->move(this_object());
   
   reset_room();
}
