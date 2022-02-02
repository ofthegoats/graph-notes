#!/usr/bin/env runhaskell

import GHC.IO.Exception (ExitCode (ExitFailure, ExitSuccess))
import System.Process (system)

-- map of test files and compiler dependencies
files :: [(String, [String])]
files =
  [ ("linked_list_test.c", ["../linked_list.c"]),
    ("graph_test.c", ["../graph.c", "../linked_list.c"])
  ]

runtest :: (String, [String]) -> IO ()
runtest (file, deps) = do
  putStrLn $ "TESTING: " ++ file
  comp_code <- system $ "clang -g " ++ unwords (file : deps) ++ " -o ./a.out"
  case comp_code of
    ExitFailure a -> putStrLn $ "COMPILATION ERROR: " ++ file
    ExitSuccess -> do
      run_code <- system "./a.out"
      case run_code of
        ExitFailure a -> putStrLn $ "FAILED: " ++ file
        ExitSuccess -> putStrLn $ "PASSED: " ++ file

main :: IO ()
main = mapM_ runtest files
