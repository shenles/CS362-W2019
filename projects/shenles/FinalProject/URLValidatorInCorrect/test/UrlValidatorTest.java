//import junit.framework.TestCase;
import java.util.Random;

//public class UrlValidatorTest extends TestCase {

//   public UrlValidatorTest(String testName) {
//      super(testName);
//   }

public class UrlValidatorTest {
 
  public static void main(String[] args) {
      UrlValidator ourUVObj = new UrlValidator();
      randomTest(ourUVObj); 
  } 
   /* return the result of isValid on the URL
   * return 0 if isValid finds no problems with the URL
   * return 1 otherwise */ 
   public static int resIsValid(String url, UrlValidator uvObj) {
      if (uvObj.isValid(url)) {
        return 0;
      } else {
        return 1;
      }
   } 
 
   /* show the results of the current test
   * compare the result of isValid with the expected value
   * if actual matches expected, test passes
   * otherwise, test fails */ 
   public static void showTestRes(String url, int expected, UrlValidator uvObj) {
      if (resIsValid(url, uvObj) == 0 && expected == 0) {
         System.out.print("Passed: " + url + " correctly marked valid\n"); 
      } else if (resIsValid(url, uvObj) == 1 && expected == 1) {
         System.out.print("Passed: " + url + " correctly marked invalid\n");
      } else if (resIsValid(url, uvObj) == 0 && expected == 1) {
         System.out.print("*FAILED*: " + url + " incorrectly marked valid\n");
      } else if (resIsValid(url,uvObj) == 1 && expected == 0) {
         System.out.print("*FAILED*: " + url + " incorrectly marked invalid\n");
      }
   } 

   /* handle random testing for 4 input partitions */
   public static void randomTest(UrlValidator uvObj) {
      System.out.print("\nRandom Testing\n\n");

      // create random generator
      Random randGen = new Random();
      
      // arrays of valid and invalid schemes 
      String[] validSchemes = {"http", "https", "ftp"}; 
      String[] invalidSchemes = {"htp", "htps", "httpr", "HTTP", "ftP", "ftps", "file", "telnet", "news", " ", "", "ssh", "tftp", "mailto", "data", "app", "svn", "tel", "ftp?", "htt.p", "http.", "x", "zz", "..."}; 

      // arrays of valid and invalid authorities
      String[] validAuths = {"www.google.com", "oregonstate.edu", "www.nasa.gov", "www.pbs.org", "www.bitpaper.io", "ir.aboutamazon.com", "en.wikipedia.org"}; 
      String[] invalidAuths = {"ww.google.com", "w.google.com", "zzz.google.com", "www..yahoo.com", "", " ", "www,goodreads.com", "www.yahoo,com", "www:yahoo.com", "www.youtube:com", "www.youtube.com:", "www.nasa.gob", ":www.nasa.gov", "www/google.com"};

      // arrays of valid and invalid paths 
      String[] validPaths = {"/index.html", "/about/us", "/jobs", "/press", "/our-communities"};  
      String[] invalidPaths = {"//index.html", "/about//", "nope", "::contact.", ">!badpath", "/bad path/"}; 

      // arrays of valid and invalid queries
      String[] validQuers = {"title=Query_string&action=edit", "field1=val1&field2=val2", "example=query", "", "ref=ftr"}; 
      String[] invalidQuers = {"//badquery", "bad query", "field1=val1field2=vald2", "example==badquery", ".badquery", "badquery.", "bad::query"};


     /* BEGIN TESTING INPUT PARTITIONS */
     int testCount = 0;

     /* SCHEME: test URLs where only scheme is changed
     * other parts are constant 
     *************************************************/
     System.out.print("******Testing Scheme*******\n");

     // build random valid URL without adding scheme yet
     // get element at random index in each array 
     String restOfString = "://" + validAuths[randGen.nextInt(validAuths.length)] + validPaths[randGen.nextInt(validPaths.length)] + "?" + validQuers[randGen.nextInt(validQuers.length)]; 

     // test random valid schemes
     for (int i = 0; i < 3; i++) {
       // build the current URL by choosing a random valid scheme
       // append the rest of the URL to the current scheme 
       String currentURL = validSchemes[randGen.nextInt(validSchemes.length)] + restOfString;
       testCount++;
       System.out.print("Test " + testCount + ": ");
       showTestRes(currentURL, 0, uvObj); 
    }     

    // test random invalid schemes
    for (int j = 0; j < 18; j++) {
      String currentURL = invalidSchemes[randGen.nextInt(invalidSchemes.length)] + restOfString; 
      testCount++;
      System.out.print("Test " + testCount + ": ");
      showTestRes(currentURL, 1, uvObj);
    }

    /* AUTHORITY: test URLs where only authority changes
    * all other parts of URL are constant
    ***************************************************/
     System.out.print("******Testing Authority*******\n");
     // build random valid URL without adding authority yet 
     // get element at random index in each array 
     String restOfString1 = validSchemes[randGen.nextInt(validSchemes.length)] + "://";
     String restOfString2 = validPaths[randGen.nextInt(validPaths.length)] + "?" + validQuers[randGen.nextInt(validQuers.length)]; 

     // test valid authorities
     for (int k = 0; k < 6; k++) {
      String currentURL = restOfString1 + validAuths[randGen.nextInt(validAuths.length)] + restOfString2;
      testCount++;
      System.out.print("Test " + testCount + ": ");
      showTestRes(currentURL, 0, uvObj);
     }

      // test invalid authorities
      for (int m = 0; m < 13; m++) {
       String currentURL = restOfString1 + invalidAuths[randGen.nextInt(invalidAuths.length)] + restOfString2; 
       testCount++;
       System.out.print("Test " + testCount + ": ");
       showTestRes(currentURL, 1, uvObj);
      }

    /* PATH: test URLs where only path changes
    * all other parts of URL are constant
    ****************************************************/
    System.out.print("******Testing Path*******\n");

     // build random valid URL without adding path yet
     String restOfString3 = validSchemes[randGen.nextInt(validSchemes.length)] + "://" + validAuths[randGen.nextInt(validAuths.length)];
     String restOfString4 = "?" + validQuers[randGen.nextInt(validQuers.length)];

      // test valid paths
      for (int n = 0; n < 4; n++) {
       String currentURL = restOfString3 + validPaths[randGen.nextInt(validPaths.length)] + restOfString4;
       testCount++;
       System.out.print("Test " + testCount + ": ");
       showTestRes(currentURL, 0, uvObj);
      }
      
      // test invalid paths
      for (int p = 0; p < 5; p++) {
       String currentURL = restOfString3 + invalidPaths[randGen.nextInt(invalidPaths.length)] + restOfString4;
       testCount++;
       System.out.print("Test " + testCount + ": ");
       showTestRes(currentURL, 1, uvObj);
      }

    /* QUERY: test URLs where only query changes
    ** all other parts of URL are constant
    ****************************************************/
     System.out.print("******Testing Query*******\n");
      String restOfString5 = validSchemes[randGen.nextInt(validSchemes.length)] + "://" + validAuths[randGen.nextInt(validAuths.length)] + validPaths[randGen.nextInt(validPaths.length)] + "?";

      for (int r = 0; r < 4; r++) {
       String currentURL = restOfString5 + validQuers[randGen.nextInt(validQuers.length)]; 
       testCount++;
       System.out.print("Test " + testCount + ": ");
       showTestRes(currentURL, 0, uvObj);
      }

      for (int s = 0; s < 7; s++) {
       String currentURL = restOfString5 + invalidQuers[randGen.nextInt(invalidQuers.length)];
       testCount++;
       System.out.print("Test " + testCount + ": ");
       showTestRes(currentURL, 1, uvObj);
      }


   }


}

