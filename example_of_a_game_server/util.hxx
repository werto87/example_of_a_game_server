#ifndef EBD66723_6B6F_4460_A3DE_00AEB1E6D6B1
#define EBD66723_6B6F_4460_A3DE_00AEB1E6D6B1
#include "confu_json/confu_json.hxx"
#include "example_of_a_game_server/game/logic/allowedMoves.hxx"
#include "example_of_a_game_server/server/user.hxx"
#include <durak/game.hxx>
#include <durak/gameData.hxx>
template <typename TypeToSend>
std::string
objectToStringWithObjectName (TypeToSend const &typeToSend)
{
  std::stringstream ss{};
  ss << confu_json::type_name<TypeToSend> () << '|' << confu_json::to_json (typeToSend);
  return ss.str ();
}

template <typename T>
T
stringToObject (std::string const &objectAsString)
{
  T t{};
  boost::json::error_code ec{};
  auto jsonValue = confu_json::read_json (objectAsString, ec);
  if (ec)
    {
      std::cerr << "error while parsing string: error code: " << ec << std::endl;
      std::cerr << "error while parsing string: stringToParse: " << objectAsString << std::endl;
    }
  else
    {
      t = confu_json::to_object<T> (jsonValue);
    }
  return t;
}

durak::GameData filterGameDataByAccountName (durak::GameData const &gameData, std::string const &accountName);

// allowed moves overrides
void sendAvailableMoves (durak::Game const &game, std::list<User> const &users, AllowedMoves const &removeFromAllowedMoves = {}, AllowedMoves const &addToAllowedMoves = {});

void sendGameDataToAccountsInGame (durak::Game const &game, std::list<User> const &users);
std::vector<shared_class::Move> calculateAllowedMoves (durak::Game const &game, durak::PlayerRole playerRole);
size_t averageRating (std::vector<std::string> const &accountNames);

void printExceptionHelper (std::exception_ptr eptr);

template <class... Fs> struct overloaded : Fs...
{
  using Fs::operator()...;
};

template <class... Fs> overloaded (Fs...) -> overloaded<Fs...>;

auto const printException1 = [] (std::exception_ptr eptr) { printExceptionHelper (eptr); };

auto const printException2 = [] (std::exception_ptr eptr, auto) { printExceptionHelper (eptr); };

auto const printException = overloaded{ printException1, printException2 };

#endif /* EBD66723_6B6F_4460_A3DE_00AEB1E6D6B1 */
