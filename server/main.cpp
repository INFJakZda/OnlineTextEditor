#include "main.hpp"

char bufforFE[PAGE_X][PAGE_Y];

bool end_program = false;
struct ClientStatusTcontrol CST[CLIENT_LIMIT];

void signal_callback_handler(int signum)
{
  cout << "#DEBUG: Signum = " << signum <<endl;
  end_program = true;
  cout << "#DEBUG: Start shutdown server" << endl;
}

void signal_callback_handler_PIPE(int signum)
{
    cout << "#ERROR: caught signal SIGPIPE " << signum << "!!!!!!" << endl;
}

int main()
{
    signal(SIGINT, signal_callback_handler);
    signal(SIGPIPE, signal_callback_handler_PIPE);
    //signal(SIGPIPE, SIG_IGN);

    for(int i = 0; i < PAGE_X; i++)
        for(int j = 0; j < PAGE_Y; j++)
            bufforFE[i][j] = '\0';

    for(int i = 0; i < CLIENT_LIMIT; i++)
    {
        CST[i].descriptor = -1;
        CST[i].clientSPECIAL_ID = -1;
    }

    thread acth(accept_connections_ed);
    thread cth(control_client);
    thread acath(accept_connections_activ);

    cout << "#DEBUG: @@@@ WAIT FOR THREADS @@@@" << endl;

    acth.join();
    acath.join();
    cth.join();

    cout << "#DEBUG: @@@@ EVERYTHING IS SUCCESSIVELY CLOSED @@@@" << endl;
    return 0;
}
