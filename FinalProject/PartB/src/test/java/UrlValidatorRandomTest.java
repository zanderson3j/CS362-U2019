import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorRandomTest extends TestCase {

    public int randomURLCount = 200;
    ResultPair[] randomTestURLs = new ResultPair[randomURLCount];

    ResultPair[] urlStart = {new ResultPair("http://www.", true),
            new ResultPair("https://www.", true),
            new ResultPair("httpd://www.", true),
            new ResultPair("htttp://www.", true)};

    ResultPair[] urlMiddle = {new ResultPair("a", true),
            new ResultPair("b", true),
            new ResultPair("c", true),
            new ResultPair("d", true),
            new ResultPair("e", true),
            new ResultPair("f", true),
            new ResultPair("g", true),
            new ResultPair("h", true),
            new ResultPair("i", true),
            new ResultPair("j", true),
            new ResultPair("k", true),
            new ResultPair("l", true),
            new ResultPair("m", true),
            new ResultPair("n", true),
            new ResultPair("o", true),
            new ResultPair("p", true),
            new ResultPair("q", true),
            new ResultPair("r", true),
            new ResultPair("s", true),
            new ResultPair("t", true),
            new ResultPair("u", true),
            new ResultPair("v", true),
            new ResultPair("w", true),
            new ResultPair("x", true),
            new ResultPair("y", true),
            new ResultPair("z", true)};

    ResultPair[] urlDomain = {new ResultPair(".gov/", true),
            new ResultPair(".com/", true),
            new ResultPair(".govvvv/", false),
            new ResultPair(".commm/", false),
            new ResultPair(".com:", true)};

    ResultPair[] urlFilePathStart = {new ResultPair("a/a", true),
            new ResultPair("b/b", true),
            new ResultPair("a//a", false),
            new ResultPair("///", false),
            new ResultPair("...", true),
            new ResultPair("", true)};

    ResultPair[] urlFilePathEnd = {new ResultPair(".html", true),
            new ResultPair(".pdf", true),
            new ResultPair("", true)};



    protected void setupRandomTestURLs() {
        int urlStartIndex;
        int urlMidLength;
        int urlMidIndex;
        int urlDomainIndex;
        int urlPathIndex;
        int urlPathEndIndex;

        for (int i = 0; i<randomURLCount; i++) {

            // preset the test url to blank and true
            randomTestURLs[i] = new ResultPair("", true);

            // url start will be randomly selected
            urlStartIndex = (int)(Math.random()*(urlStart.length));
            randomTestURLs[i].item += urlStart[urlStartIndex].item;
            randomTestURLs[i].valid &= urlStart[urlStartIndex].valid;

            // url middle section must be at least 1 character long with a max of 15
            urlMidLength = (int)(Math.random()*15) + 1;
            for(int j = 0; j < urlMidLength; j++){
                urlMidIndex = (int)(Math.random()*(urlMiddle.length));
                randomTestURLs[i].item += urlMiddle[urlMidIndex].item;
                randomTestURLs[i].valid &= urlMiddle[urlMidIndex].valid;
            }

            // url domain will be randomly selected
            urlDomainIndex = (int)(Math.random()*(urlDomain.length));
            randomTestURLs[i].item += urlDomain[urlDomainIndex].item;
            randomTestURLs[i].valid &= urlDomain[urlDomainIndex].valid;

            // url file path will be randomly selected
            urlPathIndex = (int)(Math.random()*(urlFilePathStart.length));
            randomTestURLs[i].item += urlFilePathStart[urlPathIndex].item;
            randomTestURLs[i].valid &= urlFilePathStart[urlPathIndex].valid;

            // url file path end will be randomly selected
            urlPathEndIndex = (int)(Math.random()*(urlFilePathEnd.length));
            randomTestURLs[i].item += urlFilePathEnd[urlPathEndIndex].item;
            randomTestURLs[i].valid &= urlFilePathEnd[urlPathEndIndex].valid;

        }
    }

    public void testIsValidRandom() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        setupRandomTestURLs();
        boolean expected;
        boolean result;
        for(int i = 0; i < randomURLCount; i++){
            expected = randomTestURLs[i].valid;
            result = urlVal.isValid(randomTestURLs[i].item);
            assertEquals(randomTestURLs[i].item,expected,result);
        }
    }
}