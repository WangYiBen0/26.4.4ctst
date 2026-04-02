#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <vector>

namespace W1ngD1nGa5ter {
std::fstream in, out, ans, log;
enum class Status {
  AC,
  WA,
  UKE,
  IE,
  FSE,
};

constexpr int LIMITATION = 3.2e6;

Status check(std::filesystem::path file_in, std::filesystem::path file_out,
             std::filesystem::path file_ans, std::filesystem::path file_log) {
  if (!std::filesystem::exists(file_in)) {
    std::cerr << "[ERROR]\"" << file_in.root_path() << "\" does not exist";
    return Status::FSE;
  }
  if (!std::filesystem::exists(file_out)) {
    std::cerr << "[ERROR]\"" << file_out.root_path() << "\" does not exist";
    return Status::FSE;
  }
  if (!std::filesystem::exists(file_ans)) {
    std::cerr << "[ERROR]\"" << file_ans.root_path() << "\" does not exist";
    return Status::FSE;
  }
  in.open(file_in, std::ios_base::in);
  out.open(file_out, std::ios_base::in);
  ans.open(file_ans, std::ios_base::in);
  log.open(file_log, std::ios_base::out);
  if (log.bad() || in.bad() || out.bad() || ans.bad()) {
    log << "[ERROR] I/O error";
    return Status::FSE;
  }

  unsigned T{};
  in >> T;

  for (unsigned i{}; i < T; ++i) {
    log << "[INFO] test #" << i << "\n";
    log << "[INFO] scanning input file...\n";
    unsigned n{};
    in >> n;
    std::vector<unsigned> p(1u << n), q(1u << n);
    for (unsigned i{}; i < (1u << n); ++i) {
      if (!(in >> p[i])) {
        log << "[ERROR] input stream crashed when reading p[" << i << "]\n";
        return Status::IE;
      }
    }
    for (unsigned i{}; i < (1u << n); ++i) {
      if (!(in >> q[i])) {
        log << "[ERROR] input stream crashed when reading q[" << i << "]\n";
        return Status::IE;
      }
    }
    log << "scanning output file...\n";
    unsigned m{};
    if (!(out >> m)) {
      log << "[ERROR] output stream crashed when reading m\n";
      return Status::WA;
    }
    if (m > LIMITATION) {
      log << "[WARNING] method's taking too long!(too many operations)\n"
          << "   [INFO] read " << m << " steps, greater than " << LIMITATION
          << "\n";
      return Status::WA;
    }
    for (unsigned i{}; i < m; ++i) {
      unsigned x{}, y{};
      if (!(out >> x >> y)) {
        log << "[ERROR] output stream crashed when reading i/j[" << i << "]\n";
        return Status::WA;
      }
      if (x == y) {
        log << "[WARNING] swapping index cannot be the same\n"
            << "   [INFO] step #" << i << ", i == j == " << x << "\n";
        return Status::WA;
      }
      if ((p[x] ^ p[y]) > (x ^ y)) {
        log << "[WARNING] p[" << x << "] and p[" << y << "] cannot swap\n"
            << "   [INFO] step #" << i << ", p[i] == " << p[x]
            << "p[j] == " << p[y] << ", p[i] ^ p[j] > i ^ j\n";
        return Status::WA;
      }
      std::swap(p[x], p[y]);
    }
    if (p != q) {
      log << "[WARNING] finally p != q\n";
      return Status::WA;
    }
    log << "[INFO] Congradulations! Test #" << i << " passed.\n";
  }

  return Status::AC;
}
} // namespace W1ngD1nGa5ter

int main(int argn, char **args) {
  std::ios_base::sync_with_stdio(false);

  std::clog << "recieved " << argn << " args:\n";
  for (int i{}; i < argn; ++i) {
    std::clog << "```\n" << args[i] << "\n```\n";
  }
  W1ngD1nGa5ter::Status result{W1ngD1nGa5ter::Status::UKE};
  switch (argn) {
  case 4: {
    result = W1ngD1nGa5ter::check(args[1], args[2], args[3], "checker.log");
  } break;
  case 5: {
    result = W1ngD1nGa5ter::check(args[1], args[2], args[3], args[4]);
  } break;
  default: {
    std::cerr << "[ERROR] 3 args required, but recieved " << argn - 1 << "\n";
    return -1;
  } break;
  }
  switch (result) {
  case W1ngD1nGa5ter::Status::AC: {
    std::cout << "Accepted.\n";
    return 0;
  } break;
  case W1ngD1nGa5ter::Status::WA: {
    std::cout << "Wrong Answer.\n";
    return 1;
  } break;
  case W1ngD1nGa5ter::Status::UKE: {
    std::cout << "Unknown Error.\n";
    return 2;
  } break;
  case W1ngD1nGa5ter::Status::FSE: {
    std::cout << "Filesystem Error.\n";
    return 3;
  } break;
  case W1ngD1nGa5ter::Status::IE: {
    std::cout << "Input Error.\n";
    return 3;
  } break;
  }
  return 0;
}
