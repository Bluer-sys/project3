#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool ip_comp(const std::vector<std::string>& a, const std::vector<std::string>& b)
{
    for(int i = 0; i < a.size(); ++i)
        if(a.at(i) != b.at(i))
            return std::stoi(a.at(i)) > std::stoi(b.at(i));
    return false;
}

void ip_print(std::vector<std::vector<std::string>>::const_iterator ip)
{
        for (decltype(auto) ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
}

template<typename... T>
auto variadic_filter(const std::vector<std::vector<std::string>>& ip_pool,T ... args)
{
    std::vector<std::vector<std::string>> ip_filter;

    int filters[sizeof...(args)] = { args... };
    for (const auto& ip : ip_pool)
    {
        int i;
        for (i = 0; i < sizeof...(args); ++i)
        {
            if (std::stoi(ip.at(i)) == filters[i])
                continue;
            else break;
            
        }
        if(i == sizeof...(args))
            ip_filter.push_back(ip);
    }
    return ip_filter;
}

int main(int argc, char const* argv[])
{
    try
    {
        std::vector<std::vector<std::string>> ip_pool;
        for (std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // Reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), ip_comp);

        for (decltype(auto) ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            ip_print(ip);
        }
        std::cout << std::endl;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Filter by first byte and output
        std::vector<std::vector<std::string>> ip_filter;
        auto filter1 = [=, &ip_pool](int filter) mutable {for (const auto& ip : ip_pool) if (stoi(ip.at(0)) == filter) ip_filter.push_back(ip); return ip_filter; }(1);
        for (decltype(auto) ip = filter1.cbegin(); ip != filter1.cend(); ++ip)
        {
            ip_print(ip);
        }
        std::cout << std::endl;
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Filter by first and second bytes and output
        auto filter2 = variadic_filter(ip_pool, 46, 70);
        for (decltype(auto) ip = filter2.cbegin(); ip != filter2.cend(); ++ip)
        {
            ip_print(ip);
        }
        std::cout << std::endl;
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        auto filter3 = [=, &ip_pool](int filter) mutable {for (const auto& ip : ip_pool) for (const auto& ip_part : ip) if (std::stoi(ip_part) == filter) { ip_filter.push_back(ip); break; } return ip_filter; }(46);
        for (decltype(auto) ip = filter3.cbegin(); ip != filter3.cend(); ++ip)
        {
            ip_print(ip);
        }
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
