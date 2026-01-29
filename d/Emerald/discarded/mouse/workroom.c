inherit "/std/workroom";

create_workroom()  {

    ::create_workroom();

      set_short("mouse hole");
      set_long("You are able to enter this tiny hole between the roots "+
           "of an ancient oak by means of a mystical enchantment. Inside "+
           "you discover the humble abode of a small rodent. The massive "+
           "roots of the tree arch overhead. The floor and "+
           "walls are comprised of earth, hard-packed and smoothened by "+
           "years of work. A large nest of old leaves and feathers "+
           "dominates the chamber. A cache of acorns fills one corner.\n");

      add_exit("/d/Genesis/wiz/virtual","virtual");
      add_exit("/d/Emerald/workroom","emerald");

}
 
