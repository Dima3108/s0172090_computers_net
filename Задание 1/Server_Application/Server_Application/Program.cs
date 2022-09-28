using System;
using System.IO;
using System.Threading;
namespace Server_Application
{
    internal class Program
    {
        public const string i_file_name = "server.txt";
        public const string o_file_name = "client.txt";
        public const int sort_command = 0, sred_value = 1, min_value = 2, max_value = 3,info_value=4;
        private static int[] work_buffer;
        private static string message;
        public const string error_command = "произошла непердвиденная ошибка";
        static void Main(string[] args)
        {
            Thread.CurrentThread.Priority = ThreadPriority.Highest;
            string i_dat;
            using (StreamReader reader = new StreamReader(File.Open(i_file_name, FileMode.OpenOrCreate, FileAccess.Read,FileShare.ReadWrite)))
            {
                using (StreamWriter writer = new StreamWriter(File.Open(o_file_name, FileMode.OpenOrCreate, FileAccess.Write,FileShare.Read),System.Text.Encoding.Unicode))
                {
                    try
                    {
                        while (true)
                        {
                            if ((i_dat=reader.ReadLine())!=null&&i_dat!="")
                            {
#if DEBUG
                                Console.WriteLine(i_dat);
#endif

                                int command = -1;
                                string h = i_dat;
                                
                                
                                string[] k = null;
                                int count = -1;
                                message = "";
                                if (int.TryParse(h, out int c))
                                {
                                    if (c == info_value)
                                    {
                                        message += "Команды:\n";
                                        message += "0 <колво целых чисел> <целые числа типа int разделенные пробелом>";
                                        message += ": возвращает отсортированные элементы\n";
                                        message += "1 <колво целых чисел> <целые числа типа int разделенные пробелом>";
                                        message += ": возвращает среднеарефметическое элементов преобразованное в целое число\n";
                                        message += "2 <колво целых чисел> <целые числа типа int разделенные пробелом>";
                                        message += ": возвращает значение минимального элемента\n";
                                        message += "3 <колво целых чисел> <целые числа типа int разделенные пробелом>";
                                        message += ": возвращает значение максимального элемента\n";
                                        message += "4 : возвращает информацию о доступных командах\n";
                                        writer.WriteLine(message);
                                        writer.Flush();
                                    }
                                   
                                }
                                else
                                {


                                    try
                                    {
                                        k = h.Split(" ");

                                        command = int.Parse(k[0]);
                                        count = int.Parse(k[1]);
                                        work_buffer = new int[count];
                                        for (int f = 2; f < k.Length; f++)
                                            work_buffer[f - 2] = int.Parse(k[f]);
                                        switch (command)
                                        {
                                            case 0:
                                                Array.Sort(work_buffer);
                                                for (int i = 0; i < work_buffer.Length; i++)
                                                    message += work_buffer[i].ToString() + " ";

                                                break;
                                            case 1:
                                                long sum = 0;
                                                for (int i = 0; i < work_buffer.Length; i++)
                                                    sum += (long)work_buffer[i];
                                                sum /= (long)work_buffer.Length;
                                                message += sum.ToString();
                                                break;
                                            case 2:
                                                int v = work_buffer[0];
                                                for (int i = 2; i < work_buffer.Length; i++)
                                                    if (work_buffer[i] < v)
                                                        v = work_buffer[i];
                                                message += v.ToString();
                                                break;
                                            case 3:
                                                int v1 = work_buffer[0];
                                                for (int i = 2; i < work_buffer.Length; i++)
                                                    if (work_buffer[i] > v1)
                                                        v1 = work_buffer[i];
                                                message += v1.ToString();
                                                break;
                                            default:
                                                throw new Exception("недопстимая команда");
                                        }
                                    }
                                    catch (Exception e)
                                    {
                                        command = -1;
                                        message += error_command + " " + e.Message;
                                    }
                                    /*if (command == -1)
                                    {
                                        writer.WriteLine(error_command);
                                    }
                                    else
                                    {

                                    }*/
                                    finally
                                    {
                                        writer.WriteLine(message);
                                        writer.Flush();
                                    }
                                }
                                
                            }
                            //Thread.Sleep(100);
                        }
                    }
                    catch
                    {

                    }
                    finally
                    {
                        reader.Close();
                        writer.Close();
                    }
                }
            }

        }
    }
    
    
}
