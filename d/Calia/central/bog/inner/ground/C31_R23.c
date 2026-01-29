//Room type 5

inherit "/d/Calia/central/bog/inner/ground/base_side";

void
create_room()
{
    create_side("C31_R23", ({"C31_R22", "C32_R22", "C32_R23",
        "C32_R24", 0, 0, 0, "C30_R22"}), "southwest");
}
