#include "Program.h"
#include "hagi/Hagi.h"

// clang-format off
Program::Option options[47]{                            
    {"h",                                   "help",                                0, "--help,                                    -h           "}, 
    {nullptr,                               "features",                            0, "--features                                 "},          
    {nullptr,                               "command",                             1, "--command=<file>                           "},          
    {"l",                                   "log",                                 1, "--log=<file>                               "},          
    {"a",                                   "ask",                                 0, "--ask,                                     -a           "}, 
    {"m",                                   "mute",                                0, "--mute                                     "},          
    {"sgww",                                "sync-guest-with-wall",                0, "--sync-guest-with-wall                     "},          
    {"sgwh",                                "sync-guest-with-wall",                0, "--sync-guest-with-wall                     "},          
    {"sgwh",                                "sync-guest-with-host",                0, "--sync-guest-with-host                     "},          
    {"sgn",                                 "sync-guest-none",                     0, "--sync-guest-none                          "},          
    {"lss",                                 "load-state-slot",                     1, "--load-state-slot=<index>,                 -lss<index>  "}, 
    {"lsf",                                 "load-state-file",                     1, "--load-state-file=<filename>,              -lsf<file"}, 
    {"dal",                                 "delete-after-load",                   0, "--delete-after-load                        "},          
    {"dim-screen-after",                    "dim-screen-after",                    1, "--dim-screen-after=<s>                     "},          
    {"volume",                              "volume",                              1, "--volume=<0..100>                          "},          
    {"screenshot-write-queue-capacity",     "screenshot-write-queue-capacity",     1, "--screenshot-write-queue-capacity=<1..n"}, 
    {"screenshot-write-queue-thread-count", "screenshot-write-queue-thread-count", 1, "--screenshot-write-queue-thread-count=<"}, 
    {"screenshot-output-format",            "screenshot-output-format",            1, "--screenshot-output-format=[png|ppm]       "},          
    {"random-inputs",                       "random-inputs",                       0, "--random-inputs                            "},          
    {"random-inputs-seed",                  "random-inputs-seed",                  1, "--random-inputs-seed=<0..n>                "},          
    {"random-inputs-period",                "random-inputs-period",                1, "--random-inputs-period=<0..n>              "},          
    {"t",                                   "test",                                1, "--test=<filename>,                         -t           "}, 
    {"gt",                                  "generatetest",                        1, "--generatetest=<directory>,                -gt          "}, 
    {"stop-failed-test",                    "stop-failed-test",                    2, "--stop-failed-test[=<number>]              "},          
    {"gui",                                 "gui",                                 0, "--gui,                                     -gui         "}, 
    {"wc",                                  "waitcontroller",                      0, "--waitcontroller,                          -wc          "}, 
    {"cfg",                                 "config",                              1, "--config=<filename>,                       -cfg         "}, 
    {"sp",                                  "screenshot-period",                   1, "--screenshot-period=<value>,               -sp          "}, 
    {"e",                                   "exit",                                1, "--exit=<value>,                            -e           "}, 
    {"r",                                   "rootdir",                             1, "--rootdir=<path>,                          -r<path>     "}, 
    {"bos",                                 "break-on-start",                      0, "--break-on-start,                          -bos         "}, 
    {"bosd",                                "break-on-start-dsp",                  0, "--break-on-start-dsp,                      -bosd        "}, 
    {"listen-address",                      "listen-address",                      1, "--listen-address=<address>                 "},          
    {"listen-port",                         "listen-port",                         1, "--listen-port=<port>                       "},          
    {"log-unit-test",                       "log-unit-test",                       0, "--log-unit-test                            "},          
    {"no-pip",                              "no-pip",                              0, "--no-pip                                   "},          
    {"card-format",                         "card-format",                         1, "--card-format=<size_in_Mbits>              "},          
    {"card-uncompressed",                   "card-uncompressed",                   0, "--card-uncompressed                        "},          
    {"card-force-copy",                     "card-force-copy",                     0, "--card-force-copy                          "},          
    {"disable-file-cache",                  "disable-file-cache",                  0, "--disable-file-cache                       "},          
    {"no-db-config",                        "no-db-config",                        0, "--no-db-config                             "},          
    {"config-override",                     "config-override",                     1, "--config-override                          "},          
    {"no-patch",                            "no-patch",                            0, "--no-patch                                 "},          
    {"gecko-patch",                         "gecko-patch",                         1, "--gecko-patch=<name>                       "},          
    {"no-dol-hash",                         "no-dol-hash",                         0, "--no-dol-hash                              "},          
    {"record-input",                        "record-input",                        0, "--record-input                             "},          
    {"play-input",                          "play-input",                          0, "--play-input                               "},          
};
// clang-format on

// NON_MATCHING
Hagi::Hagi(int argc, char** argv)
    : Program("Hagi", "*.elf; *.dol; *.iso; *.gcm; *.tgcm", options, sizeof(options)) {}
