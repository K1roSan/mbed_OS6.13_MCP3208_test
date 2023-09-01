![image](https://github.com/K1roSan/mbed_OS6.13_MCP3208_test/assets/142633814/57345b4f-3a4c-433d-ac68-ec11aea726bb)
# MCP3208 Mbed OS6.13 example

I tested with Nucleo-F303K8. 
Maybe, you can use any mbed if you change the pin assignment.

orignail code is https://os.mbed.com/users/Kemp/code/mcp3208/

If you want to use flaot value for serial write, make "mbed_app.json" file on project root directory and write like below.


{
    "target_overrides": {
        "*": {
            "target.printf_lib": "std"
        }
    }
}

![Screenshot 2023-09-01 17 53 23](https://github.com/K1roSan/mbed_OS6.13_MCP3208_test/assets/142633814/9a112225-8ddd-482c-b7c0-da02931bf387)
