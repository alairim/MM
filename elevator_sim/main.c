/* Don't include anything else from simulation/ */
#include "simulation/elevator.h"
#include "sim_ele.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    elevator_h e;

    project_s_initialize();

    /* Before we start, we must initialise the simulation */
    int ret;
    if ((ret = start_elevator(&e))) {
        fprintf(stderr, "Failed to initialise elevator simulator: %d\n", ret);
        return 1;
    }

    while (1)
    {
        sim_ele_step();

        /* Connect position */
        sim_ele_U.position = get_cart_position(e);

        /* Connect inputs */
        sim_ele_U.F0 = (get_button_state(e) & BUTTON_STATE_FLOOR0);
        sim_ele_U.F1 = (get_button_state(e) & BUTTON_STATE_FLOOR1);
        sim_ele_U.F2 = (get_button_state(e) & BUTTON_STATE_FLOOR2);
        sim_ele_U.F3 = (get_button_state(e) & BUTTON_STATE_FLOOR3);
        sim_ele_U.F4 = (get_button_state(e) & BUTTON_STATE_FLOOR4);
        sim_ele_U.Emergency = (get_button_state(e) & BUTTON_STATE_EMERGENCY);
        
        /* Connect motor */
        set_motor_speed(e, (float)sim_ele_Y.speed);

        /* Connect Error signal */
        if (sim_ele_Y.err_sig)
        {
            printf("Error signal received!!\r\n");
            break;
        }
        
        usleep(100000);

        /* Connect door */
        if (sim_ele_Y.door)
        {
            set_doors_open(e, true);
        }
        else
        {
            set_doors_open(e, false);
        }

        /* Connect lamps */
        int LAPM_STATE_Lamp = 0x00;
        if (sim_ele_Y.F0_lamp) LAPM_STATE_Lamp |= LAMP_STATE_FLOOR0;
        if (sim_ele_Y.F1_lamp) LAPM_STATE_Lamp |= LAMP_STATE_FLOOR1;
        if (sim_ele_Y.F2_lamp) LAPM_STATE_Lamp |= LAMP_STATE_FLOOR2;
        if (sim_ele_Y.F3_lamp) LAPM_STATE_Lamp |= LAMP_STATE_FLOOR3;
        if (sim_ele_Y.F4_lamp) LAPM_STATE_Lamp |= LAMP_STATE_FLOOR4;
        if (sim_ele_Y.emer_sig) LAPM_STATE_Lamp |= LAMP_STATE_EMERGENCY;
        set_lamp_state(e, LAPM_STATE_Lamp);

        /* Connect motor */
        printf("Position: %f; Speed: %f",get_cart_position(e), sim_ele_Y.speed);
    }
    
    printf("Ending...\r\n");

    /* If we decide to quit, for whatever reason, we should stop the
     * simulation. */
    stop_elevator(e);

    project_s_terminate();

    return 0;
}
