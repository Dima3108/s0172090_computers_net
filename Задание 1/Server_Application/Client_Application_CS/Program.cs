using System;
using System.IO;
namespace Client_Application_CS
{
    class Program
    {
        public const string o_file_name = "server.txt";
        public const string i_file_name = "client.txt";
        static void Main(string[] args)
        {
            using (StreamReader reader = new StreamReader(File.Open(i_file_name, FileMode.OpenOrCreate, FileAccess.Read, FileShare.ReadWrite)))
            {
                using (StreamWriter writer = new StreamWriter(File.Open(o_file_name, FileMode.OpenOrCreate, FileAccess.Write, FileShare.Read)))
                {
                    writer.WriteLine("4");
                    writer.Flush();
                    while (reader.EndOfStream)
                    {

                    }
                    while (reader.EndOfStream == false)
                    {
                        Console.WriteLine(reader.ReadLine());
                    }
                    while (true)
                    {
                        writer.WriteLine(Console.ReadLine());
                        writer.Flush();
                        while (reader.EndOfStream)
                        {

                        }
                        while (reader.EndOfStream == false)
                        {
                            Console.WriteLine(reader.ReadLine());
                        }
                    }
                }
            }
        }
    }
}
