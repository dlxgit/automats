import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class MyFileWriter {
    public static void Write(String text) {
            try {
                File f1 = new File("D:/Automats/Tables/ll/LL/lexerProject/lexerOutput.txt");
                if(!f1.exists()) {
                    f1.createNewFile();
                }
                FileWriter fileWritter = new FileWriter(f1.getAbsolutePath(),true);
                BufferedWriter bw = new BufferedWriter(fileWritter);
                bw.write(text);
                bw.newLine();
                bw.close();
            } catch(IOException e){
                e.printStackTrace();
            }
        }
}